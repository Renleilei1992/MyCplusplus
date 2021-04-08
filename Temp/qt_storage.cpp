nclude "public/storage.h"
#include "public/fileformat.h"
#include "public/tracer.h"

#include <QMutexLocker>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QProcess>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QDir>
#include <QRegExp>
#include <QDebug>
#include <QDateTime>

QLocalStorage* QLocalStorage::m_instance = nullptr;

QLocalStorage::QLocalStorage(QObject* parent)
    : QObject(parent)
	, mRoot(QVariantMap())
{
    //initialize paths
}

QLocalStorage* QLocalStorage::get()
{
    //QMutexLocker lck(&m_mutex);
    if (!m_instance) {
        m_instance = new QLocalStorage();
    }
    return m_instance;
}

///
/// \brief 获取节点
///
QVariant * QLocalStorage::Get(const QStringList & scope)
{
	bool ok = false;
	QVariant * pObj = &mRoot;
	for (int i = 0; i < scope.length(); ++i) {
		auto &name = scope[i];

		switch (pObj->type())
		{
			case QVariant::Map:
			{
				auto pMap = reinterpret_cast<QVariantMap *>(pObj->data());
				if (!pMap)
					return nullptr;

				auto it = pMap->find(name);
				if (it == pMap->end())
					return nullptr;
				
				pObj = &it.value();
			}
			break;
			case QVariant::List:
			{
				auto pArr = reinterpret_cast<QVariantList *>(pObj->data());

				auto nIdx = name.toLong(&ok);
				if (!ok)
					return nullptr;

				if (nIdx < 0)
					nIdx = pArr->length() - nIdx;

				if (nIdx >= pArr->length())
					return nullptr;

				pObj = &((*pArr)[nIdx]);
			}
			break;

			default: /// 当前的pObj应该是Map或Array
			return nullptr;
		}
	}

	return pObj;
}

///
/// \brief 获取或新建节点
///
QVariant * QLocalStorage::New(const QStringList & scope, const QVector<QVariant::Type>& types)
{
	bool ok = false;
	QVariant * pObj = &mRoot;
	for (int i = 0; i < scope.length(); ++i) {
		auto &name = scope[i];
		auto &init = i < types.length() ? QVariant(types[i]) : QVariant();

		switch (pObj->type())
		{
			case QVariant::Invalid:
			{
				*pObj = QVariantMap();
			}
			/// 此处不要加break
			case QVariant::Map:
			{
				auto pMap = reinterpret_cast<QVariantMap *>(pObj->data());
				if (!pMap)
					return nullptr;

				auto it = pMap->find(name);
				if (it == pMap->end())
					it = pMap->insert(name, init);

				if (it == pMap->end())
					return nullptr;

				pObj = &it.value();
			}
			break;
			case QVariant::List:
			{
				auto pArr = reinterpret_cast<QVariantList *>(pObj->data());

				auto nIdx = name.toLong(&ok);
				if (!ok)
					return nullptr;

				if (nIdx < 0)
					nIdx = pArr->length() - nIdx;

				if (nIdx >= pArr->length())
				{
					pArr->reserve(nIdx + 1);
					while (nIdx >= pArr->length())
						pArr->append(init);
				}

				pObj = &((*pArr)[nIdx]);
			}
			break;

			default: /// 当前的pObj应该是Map或Array
			return nullptr;
		}

		if (init.type() != QVariant::Invalid && init.type() != pObj->type())
			return nullptr;
	}

	return pObj;
}
bool QLocalStorage::Load(enStorageType type, const QString & file, const Parameters &params)
{
    QString realFilePath = file;

	QFileInfo fi(realFilePath);
    QMutexLocker lck(&m_mutex);

	QString name = (params.contains("name") ? params["name"].toString() : fi.baseName());

    auto it = mFileMap.find(name);
    if (it == mFileMap.end()) {
        theStorage* pf = nullptr;
        switch (type) {
        case eStorage_Json:
            pf = new QLocalStorage::theJsonFile();
            break;
        case eStorage_DB:
            pf = new QLocalStorage::theSqliteFile();
            break;
        case eStorage_Mem:
            pf = new QLocalStorage::theMemory();
            break;
        case eStorage_Env:
            pf = new QLocalStorage::theEnvironment();
            break;
        }

        if (pf) {
			pf->inst = this;
			pf->file = file;
            pf->type = type;
            pf->dirty = false;
			pf->name = name;
           
            it = mFileMap.insert(pf->name, pf);
        }
    }

    if (it == mFileMap.end())
        return false;

	(*it)->file = file;
    return (*it)->Load(params);
}

bool QLocalStorage::Save(const QString &name, const Parameters &params)
{
    QMutexLocker lck(&m_mutex);
    auto it = mFileMap.find(name);
    if (it != mFileMap.end())
        return (*it)->Save(params);

    return false;
}

bool QLocalStorage::HasLoaded(const QString& name)
{
	QMutexLocker lck(&m_mutex);
	return mFileMap.end() != mFileMap.find(name);
}

bool QLocalStorage::HasScope(const QString& scope)
{
    QMutexLocker lck(&m_mutex);
    return nullptr != Get(scope);
}

bool QLocalStorage::Set(const QString& key, const QVariant& val)
{
    QMutexLocker lck(&m_mutex);
	QStringList scope;
	auto file = Key(key, scope);
	if (nullptr == file)
		return false;

	return file->Set(scope, val);
}

bool QLocalStorage::Get(const QString & key, QVariant &val)
{
    QMutexLocker lck(&m_mutex);

	QStringList scope;
	auto file = Key(key, scope);
	if (nullptr == file)
		return false;

	auto pObj = Get(scope);
	if (nullptr == pObj)
		return false;

	if (!IsValue(pObj))
		return false;

	val = *pObj;
	return true;
}

long QLocalStorage::GetCount(const QString & scope)
{
	QMutexLocker lck(&m_mutex);

	auto pObj = Get(scope);
	
	if (!pObj)
		return -1;

	if (IsTable(pObj))
	{
		auto pTbl = reinterpret_cast<QVariantMap const*>(pObj->data());
		if (!pTbl->contains("__data"))
			return -1;

		auto pSet = reinterpret_cast<QVariantList const*>((*pTbl)["__data"].data());
		return pSet->length();
	}
	else if (IsObject(pObj))
	{
		auto pMap = reinterpret_cast<QVariantMap const*>(pObj->data());
		if (!pMap)
			return -1;

		return pMap->size();
	}
	else if (IsArray(pObj))
	{
		auto pArr = reinterpret_cast<QVariantList const*>(pObj->data());
		if (!pArr)
			return -1;

		return pArr->length();
	}

	return 0;
}

bool QLocalStorage::GetSubKeys(const QString & scope, QStringList& subkeys, bool absolute /*= true*/)
{
	subkeys.clear();

	QMutexLocker lck(&m_mutex);
	auto pObj = Get(scope);
    if (!pObj)
        return false;

	if (IsTable(pObj))
	{
		auto pTbl = reinterpret_cast<QVariantMap*>(pObj->data());
		if (!pTbl)
			return false;

		pObj = &(*pTbl)["__data"];
	}
	
	if (IsObject(pObj))
	{
		auto pMap = reinterpret_cast<QVariantMap const*>(pObj->data());
		if (!pMap)
			return false;

		auto keys = pMap->keys();
		for (int i = 0; absolute && i < keys.length(); ++i)
			subkeys.append(absolute ? scope + "." + keys[i] : keys[i]);
	}
	
	if (IsArray(pObj))
	{
		auto pArr = reinterpret_cast<QVariantList const*>(pObj->data());
		if (!pArr)
			return false;

		for (int i = 0; i < pArr->length(); ++i)
			subkeys.append(absolute ? scope + "[" + QString::number(i) + "]" : QString::number(i));
	}

	return true;
}

bool QLocalStorage::GetInteger(const QString &scope, const QString & key, int &nVal)
{
	bool ret = false;
    QVariant qVal;
    if (Get(scope + "." + key, qVal)) {
        nVal = qVal.toInt(&ret);
    }

    return ret;
}

bool QLocalStorage::GetULongLong(const QString & scope, const QString & key, qulonglong & val)
{
    bool ret = false;
    QVariant qVal;
    if (Get(scope + "." + key, qVal)) {
        val = qVal.toULongLong(&ret);
    }

    return ret;
}

bool QLocalStorage::GetUInteger(const QString &scope, const QString & key, unsigned int &nVal)
{
    bool ret = false;
    QVariant qVal;
    if (Get(scope + "." + key, qVal)) {
        nVal = qVal.toUInt(&ret);
    }

    return ret;
}

bool QLocalStorage::GetDouble(const QString &scope, const QString & key, double &dVal)
{
    bool ret = false;
    QVariant qVal;
    if (Get(scope + "." + key, qVal)) {
        dVal = qVal.toDouble(&ret);
    }

    return ret;
}

bool QLocalStorage::GetString(const QString &scope, const QString & key, QString &sVal)
{
    QVariant qVal;
    if (Get(scope + "." + key, qVal)) {
        sVal = qVal.toString();
        return true;
    }

    return false;
}

bool QLocalStorage::SetBoolean(const QString & scope, const QString & key, bool bVal)
{
    return Set(scope + "." + key, bVal);
}

bool QLocalStorage::SetInteger(const QString & scope, const QString & key, int nVal)
{
    return Set(scope + "." + key, nVal);
}

bool QLocalStorage::SetULongLong(const QString& scope, const QString& key, qulonglong& val)
{
    return Set(scope + "." + key, val);
}

bool QLocalStorage::SetUInteger(const QString &scope, const QString & key, unsigned int &val)
{
    return Set(scope + "." + key, val);
}

bool QLocalStorage::SetDouble(const QString & scope, const QString & key, double dVal)
{
    return Set(scope + "." + key, dVal);
}

bool QLocalStorage::SetString(const QString & scope, const QString & key, const QString & sVal)
{
    return Set(scope + "." + key, sVal);
}

bool QLocalStorage::NewScope(const QString & scope, const QVector<QVariant::Type>& types)
{
	QStringList keys;
	auto file = Key(scope, keys);
	if (nullptr == file)
		return false;

	return file->New(keys, types);
}

bool QLocalStorage::DelScope(const QString & scope)
{
	QMutexLocker lck(&m_mutex);

	QStringList keys;
	auto file = Key(scope, keys);
	if (nullptr == file)
		return false;

	if (keys.size() == 1)
		file->CleanUp();

	file->Del(keys);
	return true;
}

bool QLocalStorage::DelValue(const QString & scope, const QString & key)
{
	return DelScope(QStringList({ scope, key }).join('.'));
}

static bool ParseJsonKey(const QString & key, QStringList & scope)
{
	QStringList keys;
	for (auto it : scope) {
		QRegExp rx("^([a-zA-Z_][a-zA-Z0-9_\\-]*)(\\[\\d+\\s*(,\\s*\\d+\\s*)*\\])?$");

		Q_ASSERT(rx.isValid());

		int pos = rx.indexIn(it, 0);
		if (pos == -1)
			return false;

		QString key = rx.cap(1);
		QString dim = rx.cap(2);

		keys.push_back(key);
		if (!dim.isEmpty()) {
			rx.setPattern("(\\d+)");
			pos = 0;
			while ((pos = rx.indexIn(dim, pos)) != -1) {
				keys.push_back(rx.cap(0));
				pos += rx.matchedLength();
			}
		}
	}

	scope = keys;
	return true;
}

//////////////////////////////////////////////////////////////////////////
/// theMemory
//////////////////////////////////////////////////////////////////////////
bool QLocalStorage::theMemory::Key(const QString & key, QStringList & scope)
{
	return ParseJsonKey(key, scope);
}

bool QLocalStorage::theMemory::Set(const QStringList & scope, const QVariant & val)
{
	return inst->New_Set(scope, val);
}

bool QLocalStorage::theMemory::New(const QStringList & scope, const QVector<QVariant::Type>& types)
{
	return nullptr != inst->New(scope, types);
}

bool QLocalStorage::theMemory::Del(const QStringList & scope)
{
	return inst->New_Del(scope);
}

bool QLocalStorage::theMemory::Save(const Parameters &params)
{
    return true;
}

bool QLocalStorage::theMemory::Load(const Parameters &params)
{
	QStringList scope(name);
	if (!inst->New_Del(scope))
		return false;

	return inst->New_Set(scope, QVariantMap());
}

bool QLocalStorage::theMemory::CleanUp()
{
	return inst->New_Del({ name });
}

//////////////////////////////////////////////////////////////////////////
/// theEnvironment
//////////////////////////////////////////////////////////////////////////
bool QLocalStorage::theEnvironment::Key(const QString & key, QStringList & scope)
{
	return scope.size() == 2;
}

bool QLocalStorage::theEnvironment::Set(const QStringList & scope, const QVariant & val)
{
	return inst->New_Set(scope, val.toString());
}

bool QLocalStorage::theEnvironment::New(const QStringList & scope, const QVector<QVariant::Type>& types)
{
	return nullptr != inst->New(scope, types);
}

bool QLocalStorage::theEnvironment::Del(const QStringList & scope)
{
	return inst->New_Del(scope);
}

bool QLocalStorage::theEnvironment::Save(const Parameters &params)
{
	QStringList keys;
	if (false == inst->GetSubKeys(file, keys, false))
		return false;

	QVariant val;
    for (auto key : keys) {
		if (inst->New_Get({ file, key }, val)) {
			qputenv(key.toLocal8Bit(), val.toString().toLocal8Bit());
		}
    }
    return true;
}

bool QLocalStorage::theEnvironment::Load(const Parameters &params)
{
	CleanUp();
	QStringList scope(name);

	if (!inst->New_Set(scope, QVariantMap()))
		return false;

    auto items = QProcess::systemEnvironment();
	QRegExp rx("^(\\w+)=(.*)$");

    for (auto item : items) {
		if (-1 != rx.indexIn(item, 0))
		{
			scope.push_back(rx.cap(1));
			inst->New_Set(scope, rx.cap(2));
			scope.pop_back();
		}
    }

    return true;
}

bool QLocalStorage::theEnvironment::CleanUp()
{
	return inst->New_Del({ name });
}

//////////////////////////////////////////////////////////////////////////
/// theJsonFile
//////////////////////////////////////////////////////////////////////////
bool QLocalStorage::theJsonFile::Key(const QString & key, QStringList & scope)
{
	return ParseJsonKey(key, scope);
}

bool QLocalStorage::theJsonFile::Set(const QStringList & scope, const QVariant & val)
{
	return inst->New_Set(scope, val);
}

bool QLocalStorage::theJsonFile::New(const QStringList & scope, const QVector<QVariant::Type>& types)
{
	return nullptr != inst->New(scope, types);
}

bool QLocalStorage::theJsonFile::Del(const QStringList & scope)
{
	return inst->New_Del(scope);
}

/// 保存文件
bool QLocalStorage::theJsonFile::Save(const Parameters &params)
{
	if (!params.contains("file"))
		return false;

	auto file = params["file"].toString();

	auto root = inst->Get(file);
	if (nullptr == root || root->type() != QVariant::Map)
		return false;

	auto pMap = reinterpret_cast<QVariantMap*>(root->data());
	if (nullptr == pMap)
		return false;

	QJsonObject obj = QJsonObject::fromVariantMap(*pMap);

	// 保存文件
	QJsonDocument doc(obj);
	QString json = doc.toJson(QJsonDocument::Indented);

	QFileInfo info(file);
	QFile fs(info.absoluteFilePath());

	if (fs.open(QIODevice::WriteOnly | QIODevice::Text)) {
		fs.write(json.toUtf8());
		fs.close();

		return true;
	}

	dirty = false;
	return true;
}

/// 加载文件
bool QLocalStorage::theJsonFile::Load(const Parameters &params)
{
	CleanUp();

	QFileInfo fi(file);
	QFile fs(fi.absoluteFilePath());

	if (false == fs.open(QIODevice::ReadOnly))
		return false;

	QByteArray data = fs.readAll();
	
	if (CFileFormat::isCrypted(data.constData()) && !CFileFormat::parse(data, data))
		return false;
	
	fs.close();
	QJsonParseError err;
	QJsonDocument json = QJsonDocument::fromJson(data, &err);

	return inst->New_Set({ name }, json.toVariant());
}

bool QLocalStorage::theJsonFile::CleanUp()
{
	return inst->New_Del({ name });
}

bool QLocalStorage::theSqliteFile::Key(const QString & keys, QStringList & scope)
{
	scope.clear();
	/// 链接.表名[行号].字段名字段索引或 链接.表名.主键值.字段名
	/// 链接和表名使用字母或下划线开头只能使用字母数字和下划线命名
	/// 链接.表名.主键值 可以用于仅有两列的特殊表
	QRegExp rx("^([a-zA-Z_][a-zA-Z_\\d]+).([a-zA-Z_][a-zA-Z_\\d]+)((\\[(\\d+)\\])|(.([\\w\\-]+)))?(.([\\w\\-]+))?$");

	if (rx.indexIn(keys, 0) == -1)
		return false;

	/// conn
	scope.append(rx.cap(1));
	/// table
	scope.append(rx.cap(2));
	/// row 若没有值则表明是通过Key来取值的
	row = rx.cap(5);
	/// key
	key = rx.cap(7);
	/// col 
	col = rx.cap(9);

	/// 只有Col没有Row则表示此次查询是通过Key值查询Value
	auto pObj = inst->Get(scope);
	if (!pObj || pObj->type() != QVariant::Map)
		return false;

	/// __data
	scope.append("__data");

	auto pTbl = reinterpret_cast<QVariantMap*>(pObj->data());
	if (!pTbl)
		return false;

	auto pData = reinterpret_cast<QVariantList*>((*pTbl)["__data"].data());
	if (!pData)
		return false;

	auto pInfo = reinterpret_cast<stTableInfo_t*>((*pTbl)["__info"].data());
	if (!pInfo)
		return false;

	if (!key.isEmpty() && row.isEmpty())
	{
		/// 先用笨办法遍历查找
		int i = 0;
		while (i < pData->length()) {
			if ((*pData)[i].type() != QVariant::List)
				return false;

			auto pRow = reinterpret_cast<QVariantList*>((*pData)[i].data());
			if (!pRow)
				return false;

			if (key == pRow->at(pInfo->pkey))
				break;

			++i;
		}

		scope.append(QString::number(i));

		if (pInfo->fields.length() == 2 && col.isEmpty() && i < pData->length())
		{
			/// 省略col时赋予默认值
			col = pInfo->pkey ? pInfo->fields[0].name : pInfo->fields[1].name;
		}
	}
	else if (!row.isEmpty() && key.isEmpty())
	{
		/// 行号
		scope.append(row);
	}

	if (!col.isEmpty())
	{
		/// 查找字段
		int idx = 0;
		for (auto &field : pInfo->fields) {
			if (col == field.name)
				break;

			++idx;
		}

		if (idx >= pInfo->fields.length())
			return false;

		scope.append(QString::number(idx));
	}

	return true;
}

bool QLocalStorage::theSqliteFile::Set(const QStringList & scope, const QVariant & val)
{
	/// 获取表对象
	auto pObj = inst->Get(scope.mid(0, 2));
	if (!inst->IsTable(pObj))
		return false;

	auto pTbl = reinterpret_cast<QVariantMap*>(pObj->data());
	if (!pObj)
		return false;

	auto pInfo = reinterpret_cast<stTableInfo_t*>((*pTbl)["__info"].data());
	if (!pInfo)
		return false;

	bool ok = false;
	auto iRow = scope[3].toInt(&ok);
	if (!ok)
		return false;

	/// 获取数据表 QVariantList每项都是一个QVariantList保存行数据
	auto pData = reinterpret_cast<QVariantList*>((*pTbl)["__data"].data());
	if (!pData)
		return false;

	if (scope.size() == 4)
	{
		/// 有行号没有字段名设置整行
		/// 若val是列表则要求列表项个数和字段个数要保持一致
		/// 若val是对象则根据字段依次设置
		bool ok = false;
		auto nRow = scope[3].toInt(&ok);
		if (!ok)
			return false;

		bool bNew = nRow >= pData->length();

		if (bNew) {
			auto row = pInfo->newone;
			/// 初始化行数据
			if (!key.isEmpty())
			{
				auto &field = pInfo->fields[pInfo->pkey];
				bool ok = true;
				if (field.type.compare("text", Qt::CaseInsensitive) == 0)
					row[pInfo->pkey] = key;
				else if (field.type.compare("integer", Qt::CaseInsensitive) == 0)
					row[pInfo->pkey] = key.toInt(&ok);
				else if (field.type.compare("real", Qt::CaseInsensitive) == 0)
					row[pInfo->pkey] = key.toDouble(&ok);
				else
					return false;

				if (!ok)
					return false;
			}

			for (auto i = pData->length(); i <= nRow; ++i)
				pData->push_back(row);
		}

		auto pRow = reinterpret_cast<QVariantList*>((*pData)[nRow].data());
		if (!pRow)
			return false;


		QVector<int> updated;
		QVariant pkey = (*pRow)[pInfo->pkey];

		if (inst->IsValue(&val))
		{
			// Key-Value
			for (int i = 0; i < pInfo->fields.length(); ++i) {
				if (!pInfo->fields[i].pkey) {
					(*pRow)[i] = val;
					updated.push_back(i);
					break;
				}
			}
		}
		else if (inst->IsArray(&val))
		{
			auto pVal = reinterpret_cast<QVariantList const*>(val.data());
			for (int i = 0; i < pInfo->fields.length() && i < pVal->length(); ++i) {
				if (!pInfo->fields[i].pkey && (*pRow)[i] != pVal->at(i)) {
					(*pRow)[i] = pVal->at(i);
					updated.push_back(i);
				}
			}
		}
		else if (inst->IsObject(&val))
		{
			auto pVal = reinterpret_cast<QVariantMap const*>(val.data());
			for (int i = 0; i < pInfo->fields.length(); ++i) {
				auto it = pVal->find(pInfo->fields[i].name);
				if (it != pVal->end() && (*pRow)[i] != it.value()) {
					(*pRow)[i] = it.value();
					updated.push_back(i);
				}
			}
		}

		if (bNew)
		{
			if (!pInfo->Insert(pRow))
				return false;
		}
		else
		{
			/// 标记修改
			if (!pInfo->Update(pRow, updated, pkey))
				return false;
		}
	}

	if (scope.size() == 5)
	{
		/// 行号和字段都有则设置对应的单元格
		if (!inst->IsValue(&val))
			return false;

		/// 验证行号是否在范围内
		if (iRow < 0 || iRow >= pData->length())
			return false;

		/// 设置数据
		auto pRow = reinterpret_cast<QVariantList*>((*pData)[iRow].data());
		if (!pRow)
			return false;

		/// 转为列索引
		auto idx = scope[4].toInt(&ok);
		if (!ok)
			return false;

		/// 单元格赋值
		if (!inst->New_Set(scope, val))
			return false;

		/// 标记行变更
		if (!pInfo->Update(pRow, idx, val))
			return false;

		return true;
	}

	return true;
}

bool QLocalStorage::theSqliteFile::New(const QStringList & scope, const QVector<QVariant::Type>& types)
{
	/// conn.table.__data.row.col
	if (scope.length() != 4)
		return false;

	if (inst->Get(scope))
		return false;

	/// 获取表对象
	auto pObj = inst->Get(scope.mid(0, 2));
	if (!inst->IsTable(pObj))
		return false;

	auto pTbl = reinterpret_cast<QVariantMap*>(pObj->data());
	if (!pObj)
		return false;

	auto pInfo = reinterpret_cast<stTableInfo_t*>((*pTbl)["__info"].data());
	if (!pInfo)
		return false;

	/// 插入数据
	QVariantList row = pInfo->newone;

	/// 初始化行数据
	if (!key.isEmpty())
	{
		auto &field = pInfo->fields[pInfo->pkey];
		bool ok = true;
		if (field.type.compare("text", Qt::CaseInsensitive) == 0)
			row[pInfo->pkey] = key;
		else if (field.type.compare("integer", Qt::CaseInsensitive) == 0)
			row[pInfo->pkey] = key.toInt(&ok);
		else if (field.type.compare("real", Qt::CaseInsensitive) == 0)
			row[pInfo->pkey] = key.toDouble(&ok);
		else
			return false;

		if (!ok)
			return false;
	}

	if (!inst->New_Set(scope, row))
		return false;

	if (!pInfo->Insert(&row))
		return false;

	return true;
}

bool QLocalStorage::theSqliteFile::Del(const QStringList & scope)
{
	auto pObj = inst->Get(scope.mid(0, 2));
	if (!pObj || !inst->IsTable(pObj))
		return false;

	auto pTbl = reinterpret_cast<QVariantMap*>(pObj->data());
	if (!pTbl)
		return false;

	auto pInfo = reinterpret_cast<stTableInfo_t*>((*pTbl)["__info"].data());
	if (!pInfo)
		return false;

	/// conn.table.__data.row.field
	if (scope.size() == 5)
	{
		bool ok = false;
		int idx = scope[4].toInt(&ok);
		if (!ok)
			return false;

		inst->New_Set(scope, pInfo->fields[idx].defaultValue);
	}

	/// conn.table.__data.row
	if (scope.size() == 4)
	{
		auto pObj = inst->Get(scope);
		if (!pObj)
			return false;

		auto pRow = reinterpret_cast<QVariantList*>(pObj->data());
		if (!pRow)
			return false;

		auto pKey = (*pRow)[pInfo->pkey];

		if (!inst->New_Del(scope))
			return false;

		if (!pInfo->Delete(pKey))
			return false;
	}

	return true;
}

bool QLocalStorage::theSqliteFile::Upgrade(const QString& db_database, const QString& db_filename)
{
	QFileInfo fi(db_filename);

	QFile fs(fi.absoluteFilePath());
	if (!fs.open(QFile::ReadOnly))
		return false;

	// 打开数据库配置文件
	QByteArray data = fs.readAll();
	
	if (CFileFormat::isCrypted(data.constData()) && !CFileFormat::parse(data, data))
		return false;

	fs.close();

	QJsonParseError err;
	QJsonDocument doc = QJsonDocument::fromJson(data, &err);

	/**************************************
	"Info2" = {
		"version" : "1.5.2.0",

		"fields" : [
			{
				"name" : "cmdline",
				"type" : "text",
				"size" : 0,
				"default" : "''",
				"collate" : "BINARY"
				"null" : False,
				"conflict" : "ABORT",
			},
		]
	}
	**************************************/

	if (!doc.isObject()) {
		int last = 0;
		int line = 1;
		do {
			int next = data.indexOf('\n', last);
			if (next > err.offset)
				break;
			last = next + 1;
			line++;
		} while (true);

		TRACEE("%s, line = %d, column = %d", qPrintable(err.errorString()), line, err.offset - last);
		return false;
	}

	if (!doc.isObject())
		return false;

	auto jo_tables = doc.object();
	/// 用来保存表和字段结构
	QMap<QString, QMap<QString, stFieldInfo_t>> tables;
	/// 用来保存需要升级的表
	QSet<QString> upgrades;

	for (auto js_tbl_name : jo_tables.keys()) {
		// 表信息
		auto jv_table = jo_tables[js_tbl_name];
		if (!jv_table.isObject())
			continue;

		auto jo_table = jv_table.toObject();

		/// 获取数据表
		if (!jo_table["fields"].isArray())
			break;

		/// 获取表字段定义
		auto ja_fields = jo_table["fields"].toArray();

		auto &fields = tables[js_tbl_name];
		/// 查询表结构
		QSqlQuery field_query = db.exec(QString("pragma table_info(%1)").arg(js_tbl_name));
		if (db.lastError().type() != QSqlError::NoError) {
			qDebug() << db.lastError().text();
			continue;
		}

		/// 遍历字段建立字段信息
		while (field_query.next()) {
			stFieldInfo_t field;
			field.cid = field_query.value("cid").toInt();
			field.name = field_query.value("name").toString();
			field.type = field_query.value("type").toString();
			field.defaultValue = field_query.value("dflt_value");
			//if default_value is '', set it to empty string
			if (field.defaultValue == "''")
				field.defaultValue = "";
			field.null = field_query.value("notnull").toBool();
			field.pkey = field_query.value("pk").toBool();
			if (field.type != "text")
			{
				qDebug()
					<< __FUNCTION__ << ": name: "
					<< field.name << ", type: "
					<< field.type << ", dflt_value: "
					<< field.defaultValue;
			}

			// 是否被索引
			fields.insert(field.name, field);
		}

		/// 遍历字段确认表字段未改动
		for (auto &jv_field : ja_fields) {
			if (!jv_field.isObject())
				break;

			auto jo_field = jv_field.toObject();
			if (!jo_field.contains("name"))
				break;

			if (!jo_field.contains("type"))
				break;

			auto field = fields.find(jo_field["name"].toString());

			// 新加字段
			if (field == fields.end()) {
				upgrades.insert(js_tbl_name);
				break;
			}

			// 类型变更
			if ((*field).type != jo_field["type"].toString()) {
				upgrades.insert(js_tbl_name);
				break;
			}

			if (jo_field.contains("default") && (*field).defaultValue != jo_field["default"].toVariant()) {
				upgrades.insert(js_tbl_name);
				break;
			}

			if (jo_field.contains("null") && (*field).null != jo_field["null"].toBool()) {
				upgrades.insert(js_tbl_name);
				break;
			}

			if (jo_field.contains("primary") && (*field).pkey != jo_field["primary"].toBool()) {
				upgrades.insert(js_tbl_name);
				break;
			}
		}
	}

	/// 升级或新建表
	for (auto js_tbl_name : jo_tables.keys()) {
		auto jv_table = jo_tables[js_tbl_name];
		if (!jv_table.isObject())
			continue;

		/// 保存老数据的表名
		QString js_old_name;

		auto jo_table = jv_table.toObject();

		//if table need update and really exist, rename it.
		if (upgrades.contains(js_tbl_name) && !tables[js_tbl_name].isEmpty()) {
			auto date = QDate::currentDate().toString("yyyyMMdd");
			auto time = QTime::currentTime().toString("hhmmss");

			js_old_name = QString("%1_%2%3")
				.arg(js_tbl_name)
				.arg(date)
				.arg(time);

			db.exec(QString("ALTER TABLE '%1' RENAME TO '%2'")
				.arg(js_tbl_name)
				.arg(js_old_name));

			if (db.lastError().type() != QSqlError::NoError) {
				qDebug() << db.lastError().text();
				continue;
			}
		}

		/// 强制建表
		auto jv_fields = jo_table["fields"];
		if (!jv_fields.isArray())
			continue;

		auto ja_fields = jv_fields.toArray();
		if (ja_fields.isEmpty())
			continue;

		/// 开始构建
		QStringList lines;
		QStringList new_names;
		QStringList exe_names;
		QString head = QString("CREATE TABLE IF NOT EXISTS \"%1\" (").arg(js_tbl_name);

		for (auto jv_field : ja_fields) {
			auto jo_field = jv_field.toObject();
			auto name = jo_field["name"].toString();
			auto type = jo_field["type"].toString();

			QString line = QString(R"("%1" %2 )").arg(name).arg(type);

			if (jo_field["notnull"].toBool(false)) {
				line += "NOT NULL ";
			}

			if (jo_field.contains("default")) {
				auto var = jo_field["default"];
				if (!type.compare("text", Qt::CaseInsensitive)) {
					line += QString(R"(DEFAULT ('%1') )").arg(var.toString());
				} else if (!type.compare("integer", Qt::CaseInsensitive)) {
					line += QString("DEFAULT (%1) ").arg(var.toInt());
				} else if (!type.compare("real"), Qt::CaseInsensitive) {
					line += QString("DEFAULT (%1) ").arg(var.toDouble());
				} else {
					line += QString("DEFAULT (%1) ").arg(var.toString());
				}
			}

			if (jo_field["primary"].toBool(false)) {
				line += "PRIMARY KEY ";

				if (jo_field["autoincrement"].toBool(false)) {
					line += "AUTOINCREMENT ";
				}
			}

			lines.append(line);
			new_names.append(QString("\"%1\"").arg(name));
		}

		QString tail = ");";
		/// 拼出完整的建表语句
		QString sql = head + lines.join(',') + tail;

		db.exec(sql);
		if (db.lastError().type() != QSqlError::NoError) {
			qDebug() << db.lastError().text();
			continue;
		}

		/// 将原表数据插入到新表中
		if (!upgrades.contains(js_tbl_name))
			continue;

		/// 按新字段遍历老数据
		auto &fields = tables[js_tbl_name];
		for (auto &field : fields) {
			auto name = QString("\"%1\"").arg(field.name);
			if (new_names.contains(name))
				exe_names.append(name);
		}

		///只有确实存在旧数据时才需要执行插入
		if (!new_names.isEmpty() && !exe_names.isEmpty()) {
			/// 拼数据插入语句
			sql = QString("INSERT INTO \"%1\" (%2) SELECT %2 FROM \"%3\";")
				.arg(js_tbl_name)
				.arg(exe_names.join(','))
				.arg(js_old_name)
				;

			db.exec(sql);
			if (db.lastError().type() != QSqlError::NoError) {
				qDebug() << db.lastError().text();
				continue;
			}
		}
	}
	
	return true;
}

/// 加载文件
bool QLocalStorage::theSqliteFile::Load(const Parameters &params)
{
	// params
	/*
	{
		/// 数据库描述文件的文件名
		"db_filename" = "aaa",
		/// 数据库名
		"db_database" = "main",
		/// 用户名
		"db_username" = "xxxx",
		/// 密码
		"db_password" = "xxxx"
	}
	*/

	/// 字符串参数
	QString db_filename, db_database, db_username, db_password;

	/// 布尔参数
	db_filename = params.value("db_filename").toString();
	db_username = params.value("db_username").toString();
	db_password = params.value("db_password").toString();

	QFileInfo fi(file);
	if (!QDir(fi.absoluteDir()).exists()) {
		auto path = fi.absolutePath();
		QDir().mkpath(path);
	}

	// 打开数据库
	if (QSqlDatabase::contains(name)) {
		db = QSqlDatabase::database(name);
	} else {
		db = QSqlDatabase::addDatabase("QSQLITE", name);
		db.setDatabaseName(fi.absoluteFilePath());
		if (!db_username.isEmpty())
			db.setUserName(db_username);
		if (!db_password.isEmpty())
			db.setPassword(db_password);
	}

	if (!db.open()) {
		qDebug() << db.lastError();
		return false;
	}

	if (!db_filename.isEmpty()) if (!Upgrade(db_database, db_filename))
		return false;

	//////////////////////////////////////////////////////////////////////////
	/// 开始加载数据
	//////////////////////////////////////////////////////////////////////////

	/// 查找所有的表
	QSqlQuery table_query(db);
	table_query.prepare("select tbl_name from sqlite_master where type = 'table'");
	if (!table_query.exec()) {
		qDebug() << table_query.lastError().text();
		return false;
	}

	QStringList keys(name);

	/// 遍历表
	while (table_query.next()) {
		stTableInfo_t tbl_info;
		tbl_info.name = table_query.value(0).toString();
		tbl_info.pkey = 0;

		/// 查询表结构
		QSqlQuery field_query = db.exec(QString("pragma table_info(%1)").arg(tbl_info.name));
		if (db.lastError().type() != QSqlError::NoError) {
			qDebug() << db.lastError().text();
			continue;
		}

		/// 遍历字段建立字段信息
		long idx = 0;
		while (field_query.next()) {
			stFieldInfo_t field;

			field.cid  = field_query.value("cid").toInt();
			field.name = field_query.value("name").toString();
			field.type = field_query.value("type").toString();
			field.defaultValue = field_query.value("dflt_value");
			//if default_value is '', set it to empty string
			if (field.defaultValue == "''")
				field.defaultValue = "";

			field.null = field_query.value("notnull").toBool();
			field.pkey = field_query.value("pk").toBool();

			// 记录主键
			if (field.pkey)
				tbl_info.pkey = idx;

			++idx;
			
			tbl_info.fields.append(field);
			tbl_info.newone.append(field.defaultValue);
		}

		/// 查询数据
		QSqlQuery query_records(db);
		query_records.prepare(QString("select * from %1").arg(tbl_info.name));
		if (!query_records.exec()) {
			qDebug() << query_records.lastError().text() << ", last query :" << query_records.lastQuery();
			continue;
		}

		/// 遍历所有数据, 必须有主键
		QVariantList tbl_data;
		while (query_records.next()) {
			/// 抓取记录字段值
			QVariantList row;

			for (auto i = 0; i < tbl_info.fields.length(); ++i) {
				/// 将字段值压入记录行
				row.append(query_records.value(i));
			}

			tbl_data.push_back(row);
		}

		keys.push_back(tbl_info.name);

		/// conn.table.__data.row.col
		/// conn.table.__info.col

		/// 插入表数据
		keys.push_back("__data");
		inst->New_Set(keys, tbl_data);
		keys.pop_back();

		/// 插入表结构
		keys.push_back("__info");
		inst->New_Set(keys, QVariant::fromValue(tbl_info));
		keys.pop_back();
		keys.pop_back();
	}

	return true;
}

bool QLocalStorage::theSqliteFile::CleanUp()
{
	// 清理对应的db连接.
	if (QSqlDatabase::contains(name)) {
		QSqlDatabase::removeDatabase(name);
	}

	return inst->New_Del({ name });
}

/// 保存文件
bool QLocalStorage::theSqliteFile::Save(const Parameters &params)
{
	if (!db.isOpen())
		return false;

	auto pObj = inst->Get(name);
	if (!pObj)
		return false;

	if (pObj->type() != QVariant::Map)
		return false;

	auto pMap = reinterpret_cast<QVariantMap*>(pObj->data());
	if (!pMap)
		return false;


	/// 遍历所有表
	for (auto &tbl : *pMap) {
		if (tbl.type() != QVariant::Map)
			continue;

		auto pTbl = reinterpret_cast<QVariantMap*>(tbl.data());
		if (!pTbl)
			continue;

		auto pInfo = reinterpret_cast<stTableInfo_t*>((*pTbl)["__info"].data());
		if (!pInfo)
			continue;

		for (auto &it : pInfo->modified) {
			QSqlQuery query(db);
			query.prepare(it[0].toString());
			for (int i = 1; i < it.length(); ++i) {
				query.bindValue(i - 1, it[i]);
			}

			if (!query.exec())
			{
				auto e = query.lastError();
				qDebug()
					<< e.databaseText()
					<< e.text()
					<< query.lastQuery();
			}
		}

		pInfo->modified.clear();
	}

	return true;
}

#include <QDir>
void q_local_storage_test()
{
    QString qVal;
    QLocalStorage::get()->Load(QLocalStorage::eStorage_Mem, "Mem");
    QLocalStorage::get()->NewScope("Mem.web.main");
    QLocalStorage::get()->NewScope("Mem.web.dialog");
    QLocalStorage::get()->SetString("Mem.web.dialog", "appId", "1114");
    QLocalStorage::get()->SetString("Mem.web.main", "username", "albertclass");
    QLocalStorage::get()->GetString("Mem.web.main", "username", qVal);

    QLocalStorage::get()->DelScope("Mem.web.dialog");
    QLocalStorage::get()->DelScope("Mem.web.main.username");

    QLocalStorage::get()->Load(QLocalStorage::eStorage_Env, "Env");
    QLocalStorage::get()->SetString("Env", "AID", "1233");
    QLocalStorage::get()->SetString("Env", "GID", "1234");
    QLocalStorage::get()->SetString("Env", "CID", "1235");

    QLocalStorage::get()->GetString("Env", "AID", qVal);
    QLocalStorage::get()->GetString("Env", "GID", qVal);
    QLocalStorage::get()->GetString("Env", "CID", qVal);

    QLocalStorage::get()->Load(QLocalStorage::eStorage_Json, "Config/server.json");
    auto cnt = QLocalStorage::get()->GetCount("server");
    cnt = QLocalStorage::get()->GetCount("server.domainDev");
    cnt = QLocalStorage::get()->GetCount("server.themeVendor");

	QStringList keys;
	QLocalStorage::get()->GetSubKeys("server", keys);

    QLocalStorage::get()->GetSubKeys("server.domainDev", keys);
    QLocalStorage::get()->GetSubKeys("server.themeVendor", keys);

    QLocalStorage::get()->SetString("server.domainDev", "api", "http://pt.baochuangame.com");
    QLocalStorage::get()->GetString("server.domainDev", "api", qVal);

    QLocalStorage::get()->SetString("server.message", "name", "albert");
    QLocalStorage::get()->SetInteger("server.message", "age", 16);
    QLocalStorage::get()->SetDouble("Server.message", "score", 74.3);

	QFileInfo fi(qgetenv("AppData") + "\\BaoGames\\BaoGames\\all\\GameInfo.db");
	QLocalStorage::get()->Load(QLocalStorage::eStorage_DB, fi.absoluteFilePath()/*, { { "name", "GameInfo" } }*/);

    cnt = QLocalStorage::get()->GetCount("GameInfo.Task2");
    cnt = QLocalStorage::get()->GetCount("GameInfo.Task2.56");
	auto ret = QLocalStorage::get()->NewScope("GameInfo.Task2.58");

	ret = QLocalStorage::get()->GetString("GameInfo.Task2.58", "appName", qVal);
    ret = QLocalStorage::get()->GetString("GameInfo.Task2", "appName", qVal);

    ret = QLocalStorage::get()->SetString("GameInfo.Task2.58", "id", "55ffasdf");
	ret = QLocalStorage::get()->Set("GameInfo.Task2.58", QVariantMap({ {"appId", "58"}, {"appName", "857857"} }));
	ret = QLocalStorage::get()->Set("GameInfo.Task2.58", QVariantList({ 58, 58, "aaaa", "client" }));
    ret = QLocalStorage::get()->Save("GameInfo");

    QLocalStorage::get()->DelScope("GameInfo.Task2.57");
    QLocalStorage::get()->Save("GameInfo");

	fi = QFileInfo(qgetenv("AppData") + "\\BaoGames\\BaoGames\\15312169\\BaoGames");
	QLocalStorage::get()->Load(QLocalStorage::eStorage_DB, fi.absoluteFilePath()/*, { { "name", "GameInfo" } }*/);
	QLocalStorage::get()->SetInteger("BaoGames.data", "Image", 1);
	QLocalStorage::get()->SetInteger("BaoGames.data[7]", "value", 0);
	QLocalStorage::get()->SetInteger("BaoGames.data[8]", "value", 0);

    QLocalStorage::get()->NewScope("GameInfo.Task2.59");
    QLocalStorage::get()->SetString("GameInfo.Task2.59", "appName", "aaffdds");
    QLocalStorage::get()->SetString("GameInfo.Task2.59", "dirDownload", "http://download-inner/59/v1.5.3.2");
    QLocalStorage::get()->SetInteger("GameInfo.Task2.59", "gameId", 59);
    QLocalStorage::get()->SetString("GameInfo.Task2.59", "id", "ppp");
    QLocalStorage::get()->SetString("GameInfo.Task2.59", "logo", "https://ngl-backend.nos-eastchina1.126.net/qa/gameconfiguration/56/e00ba9895e15ea50421e99746ed09650.jpg");

    QLocalStorage::get()->Save("GameInfo");
}
