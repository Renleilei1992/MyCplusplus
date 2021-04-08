 once;
#ifndef __STORAGE_H__
#define __STORAGE_H__
#include "nglbase_export.h"
#include <QMap>
#include <QMutex>
#include <QVariant>
#include <QVector>
#include <QSqlDatabase>

///
/// \brief 本地存储
///
/// \author Johnny.Ren
///
class NGLBASE_EXPORT QLocalStorage : public QObject {
public:
    ///
    /// \brief 存储的类型
    ///
    /// \author Johnny.Ren
    ///
    enum enStorageType {
        eStorage_Unknow,
        eStorage_Json,
        eStorage_DB,
        eStorage_Mem,
        eStorage_Env,
    };

	enum enType {
		eValue,
		eArray,
		eTable,
		eObject,
	};

	/// 参数
	typedef QMap<QString, QVariant> Parameters;
private:
    static QLocalStorage* m_instance;
    mutable QMutex m_mutex;

    struct theStorage;
    ///
    /// \brief 文件信息
    ///
    /// \author Johnny.Ren
    ///
    struct theStorage {
		QLocalStorage* inst;
        /// 数据类型
        enStorageType type;
        /// 所属文件
        QString file;
		/// 节点名字
		QString name;
        /// 文件脏标志
        bool dirty;

		virtual bool Key(const QString &key, QStringList &scope) = 0;
        /// 设置值
        virtual bool Set(const QStringList &scope, const QVariant &val) = 0;
        /// 添加一个新节点
        virtual bool New(const QStringList &scope, const QVector<QVariant::Type> &types) = 0;
        /// 删除一个节点
        virtual bool Del(const QStringList &scope) = 0;

        /// 保存文件
        virtual bool Save(const Parameters &params) = 0;
        /// 加载文件
        virtual bool Load(const Parameters &params) = 0;
		/// 清理
		virtual bool CleanUp() = 0;
    };

    ///
    /// \brief 内存数据
    ///
    /// \author Johnny.Ren
    ///
    struct theMemory : theStorage {
		/// 解析键
		virtual bool Key(const QString &key, QStringList &scope) override;
		/// 设置值
		virtual bool Set(const QStringList &scope, const QVariant &val) override;
		/// 添加一个新节点
		virtual bool New(const QStringList &scope, const QVector<QVariant::Type> &types) override;
		/// 删除一个节点
		virtual bool Del(const QStringList &scope) override;
		/// 保存文件
        virtual bool Save(const Parameters &params) override;
        /// 加载文件
        virtual bool Load(const Parameters &params) override;
		/// 清理
		virtual bool CleanUp() override;
	};

    ///
    /// \brief 内存数据
    ///
    /// \author Johnny.Ren
    ///
    struct theEnvironment : theStorage {
		/// 解析键
		virtual bool Key(const QString &key, QStringList &scope) override;
		/// 设置值
		virtual bool Set(const QStringList &scope, const QVariant &val) override;
		/// 添加一个新节点
		virtual bool New(const QStringList &scope, const QVector<QVariant::Type> &types) override;
		/// 删除一个节点
		virtual bool Del(const QStringList &scope) override;
		/// 保存文件
        virtual bool Save(const Parameters &params) override;
        /// 加载文件
        virtual bool Load(const Parameters &params) override;
		/// 清理
		virtual bool CleanUp() override;
	};

    ///
    /// \brief Json文件
    ///
    /// \author Johnny.Ren
    ///
    struct theJsonFile : theStorage {
		/// 解析键
		virtual bool Key(const QString &key, QStringList &scope) override;
		/// 设置值
		virtual bool Set(const QStringList &scope, const QVariant &val) override;
		/// 添加一个新节点
		virtual bool New(const QStringList &scope, const QVector<QVariant::Type> &types) override;
		/// 删除一个节点
		virtual bool Del(const QStringList &scope) override;
		/// 保存文件
        virtual bool Save(const Parameters &params) override;
        /// 加载文件
        virtual bool Load(const Parameters &params) override;
		/// 清理
		virtual bool CleanUp() override;
	};

    ///
    /// \brief Sqlite文件
    ///
    /// \author Johnny.Ren
    ///
    struct theSqliteFile : theStorage {
		
        QSqlDatabase db;
		enum enRecordStatus { eRow_Update = 1, eRow_Insert = 2, eRow_Delete = 4 };

		struct stFieldInfo_t {
			/// 字段ID
			long cid;
			/// 字段名
			QString name;
			/// 字段类型
			QString type;
			/// 可否空值
			bool null;
			/// 是否主键
			bool pkey;
			/// 默认值
			QVariant defaultValue;
		};

		struct stTableInfo_t {
			/// 表名
			QString name;
			/// 主键索引
			long pkey;
			/// 字段信息
			QVector<stFieldInfo_t> fields;
			/// 修改记录
			QVector<QVariantList> modified;
			/// 新行
			QVariantList newone;

			/// 设置修改标记
			bool Update(const QVariantList* pNew, const QVector<int>& updated, const QVariant& updateKey)
			{
				QVariantList lst;

				QStringList set;
				QVariantList values;
				for (auto idx : updated)
				{
					set.append(QString("%1=?").arg(fields[idx].name));
					values.append((*pNew)[idx]);
				}

				if (set.isEmpty())
					return true;

				auto sql = QString("update %1 set %2 where %3=?")
					.arg(name)
					.arg(set.join(","))
					.arg(fields[pkey].name);

				/// Sql
				lst.append(sql);
				/// 绑定的值
				lst.append(values);
				lst.append(updateKey);

				modified.append(lst);
				return true;
			}

			bool Update(const QVariantList* pOld, int idx, const QVariant& val)
			{
				QVariantList lst;

				auto sql = QString("update %1 set %2=? where %3=?")
					.arg(name)
					.arg(fields[idx].name)
					.arg(fields[pkey].name);

				/// Sql
				lst.append(sql);
				/// 绑定的值
				lst.append(val);
				lst.append(pOld->at(pkey));

				modified.append(lst);
				return true;
			}

			bool Delete(const QVariant& key)
			{
				QVariantList lst;
				auto sql = QString("delete from %1 where %2=?")
					.arg(name)
					.arg(fields[pkey].name);

				/// Sql
				lst.append(sql);
				/// 绑定的值
				lst.append(key);

				modified.append(lst);
				return true;
			}

			bool Insert(const QVariantList* pNew)
			{
				QVariantList lst;

				/// 遍历所有字段
				QStringList fieldnames;
				QStringList placeholders;

				/// 拼装查询字符串
				QString  p_key;
				QVariant p_val;
				for (auto &field : fields) {
					fieldnames.append(field.name);
					placeholders.append("?");
				}

				auto sql = QString("insert into %1 (%2) values(%3)")
					.arg(name)
					.arg(fieldnames.join(','))
					.arg(placeholders.join(','));

				/// Sql
				lst.append(sql);
				/// 绑定的值
				lst.append(*pNew);

				modified.append(lst);

				return true;
			}
		};

		/// 行号
		QString row;
		/// 键值
		QString key;
		/// 列名
		QString col;

		/// 解析键
		virtual bool Key(const QString &key, QStringList &scope) override;
		/// 设置值
		virtual bool Set(const QStringList &scope, const QVariant &val) override;
		/// 添加一个新节点
		virtual bool New(const QStringList &scope, const QVector<QVariant::Type>& types) override;
		/// 删除一个节点
		virtual bool Del(const QStringList &scope) override;
		/// 保存文件
        virtual bool Save(const Parameters &params) override;
        /// 加载文件
        virtual bool Load(const Parameters &params) override;
		/// 清理
		virtual bool CleanUp() override;

		/// 升级
		bool Upgrade(const QString& db_database, const QString& db_filename);
    };

	/// 注册自定义类型
	friend struct QMetaTypeId<QLocalStorage::theSqliteFile::stTableInfo_t>;

    /// 文件映射表用于映射顶层Field与文件名
    QMap<QString, theStorage*>	mFileMap;

	/// 根元素
	mutable QVariant mRoot;

private:
	///
	/// \brief 解析键值并返回解析后的域数组和对应的对象指针
	///
	QLocalStorage::theStorage* Key(const QString &key, QStringList& scope)
	{
		scope = key.split(".");
		if (scope.isEmpty())
			return nullptr;

		auto it = mFileMap.find(scope.first());
		if (it == mFileMap.end())
			return nullptr;

		auto storage = it.value();

		if (scope.length() == 1)
			return storage;

		if (!storage->Key(key, scope))
			return nullptr;

		return storage;
	}

	///
	/// \brief 获取键值指向的对象指针
	///
	QVariant* Get(const QString &key)
	{
		QStringList scope;

		if (nullptr == Key(key, scope))
			return nullptr;

		return Get(scope);
	}
	
	///
	/// \brief 新建节点
	///
	QVariant* Get(const QStringList &scope);

	///
	/// \brief 获取或新建节点
	///
	QVariant* New(const QStringList & scope, const QVector<QVariant::Type>& types = QVector<QVariant::Type>());

	///
	/// \brief 设置指定的元素值
	///
	bool New_Set(const QStringList &scope, const QVariant& val)
	{
		auto pObj = New(scope);
		if (nullptr == pObj)
			return false;

		*pObj = val;
		return true;
	}

	///
	/// \brief 获取指定的元素值
	///
	bool New_Get(const QStringList &scope, QVariant &val)
	{
		auto pObj = Get(scope);
		if (nullptr == pObj)
			return false;

		val = *pObj;
		return true;
	}

	///
	/// \brief 删除指定的元素
	///
	bool New_Del(const QStringList &scope)
	{
		if (scope.empty())
			return true;

		auto pObj = Get(scope.mid(0, scope.length() - 1));
		if (nullptr == pObj)
			return false;

		bool ok = false;
		switch (pObj->type()) {
			case QVariant::Map:
			{
				auto pMap = reinterpret_cast<QVariantMap*>(pObj->data());
				if (!pMap)
					return false;

				pMap->remove(scope.last());
			}
			break;
			case QVariant::List:
			{
				auto pLst = reinterpret_cast<QVariantList*>(pObj->data());
				if (!pLst)
					return false;

				auto nIdx = scope.last().toLong(&ok);
				if (!ok)
					return false;

				if (nIdx < 0 || nIdx >= pLst->length())
					return false;

				pLst->removeAt(nIdx);
			}
			break;
		}

		return true;
	}

private:
    QLocalStorage(QObject* parent = nullptr);

public:
    static QLocalStorage* get();

    ///
    /// \brief 载入配置
    ///
    /// \Param sFile 文件路径可以是绝对路径或相对路径
    ///
    /// \Param eType 文件类型
    ///
    /// \author Johnny.Ren
    ///
    bool Load(enStorageType type, const QString &file = QString(), const Parameters &params = Parameters());

    ///
    /// \brief 判断指定配置文件是否已加载
    ///
    /// \Param sName 配置文件名基本名server.json对应的为server
    ///
    /// \author Johnny.Ren
    ///
    bool HasLoaded(const QString& name);

    ///
    /// \brief 判断指定Scope是否存在
    ///
    /// \Param scope 
    ///
    /// \author Johnny.Ren
    ///
    bool HasScope(const QString& key);

    ///
    /// \brief 保存配置
    ///
    /// \author Johnny.Ren
    ///
    bool Save(const QString &name = QString(), const Parameters &params = Parameters());

    ///
    /// \brief 获取节点下的子项数量
    ///
    /// \author Johnny.Ren
    ///
    long GetCount(const QString &scope);

    ///
    /// \brief 获取节点下的子节点列表
    ///
    /// \author Johnny.Ren
    ///
    bool GetSubKeys(const QString &scope, QStringList& subkeys, bool absolute = true);

	///
	/// \brief 是否是值类型
	///
	bool IsValue(const QVariant *pObj)
	{
		auto type = pObj->type();
		if (type == QVariant::Bool ||
			type == QVariant::Int ||
			type == QVariant::UInt ||
			type == QVariant::LongLong ||
			type == QVariant::ULongLong ||
			type == QVariant::Double ||
			type == QVariant::Char ||
			type == QVariant::String)
		{
			return true;
		}

		return false;
	}

	///
	/// \brief 是否是值类型
	///
	bool IsValue(const QString &key)
	{
		QMutexLocker lck(&m_mutex);

		auto pObj = Get(key);
		if (nullptr == pObj)
			return false;

		return IsValue(pObj);
	}

	///
	/// \brief 是否数值类型
	///
	bool IsObject(const QVariant *pObj)const
	{
		return pObj && pObj->type() == QVariant::Map;
	}

	///
	/// \brief 是否是对象类型
	///
	bool IsObject(const QStringList &scope)
	{
		QMutexLocker lck(&m_mutex);

		if (scope.empty())
			return false;

		auto pObj = Get(scope);
		if (nullptr == pObj)
			return false;

		return pObj->type() == QVariant::Map;
	}

	///
	/// \brief 是否数值类型
	///
	bool IsArray(const QVariant *pObj)const
	{
		return pObj->type() == QVariant::List;
	}

	///
	/// \brief 是否是数组类型
	///
	bool IsArray(const QStringList &scope)
	{
		QMutexLocker lck(&m_mutex);

		if (scope.empty())
			return false;

		auto pObj = Get(scope);
		if (nullptr == pObj)
			return false;

		return pObj->type() == QVariant::List;
	}

	///
	/// \brief 是否是表类型
	///
	bool IsTable(const QVariant *pObj)const
	{
		if (!IsObject(pObj))
			return false;

		auto pMap = reinterpret_cast<QVariantMap const*>(pObj->data());
		if (!pMap)
			return false;

		if (false == (pMap->contains("__data") && pMap->contains("__info")))
			return false;

		return true;
	}

	///
	/// \brief 是否是表类型
	///
	bool IsTable(const QString &key)
	{
		QMutexLocker lck(&m_mutex);

		if (key.isEmpty())
			return false;

		auto pObj = Get(key);
		if (nullptr == pObj)
			return false;

		return IsTable(pObj);
	}

    ///
    /// \brief 获取整型值
    ///
    /// \author Johnny.Ren
    ///
    bool GetInteger(const QString &scope, const QString & key, int &val);

    ///
    /// \brief 获取无符号长整型值
    ///
    /// \author Johnny.Ren
    ///
    bool GetULongLong(const QString& scope, const QString& key, qulonglong& val);

    ///
    /// \brief 获取无符号整数型
    ///
    /// \author Johnny.Ren
    ///
    bool GetUInteger(const QString &scope, const QString & key, unsigned int &val);

    ///
    /// \brief 获取浮点数
    ///
    /// \author Johnny.Ren
    ///
    bool GetDouble(const QString &scope, const QString & key, double &val);

    ///
    /// \brief 获取字符串
    ///
    /// \author Johnny.Ren
    ///
    bool GetString(const QString &scope, const QString & key, QString &val);

    ///
    /// \brief 设置布尔值
    ///
    /// \author Johnny.Ren
    ///
    bool SetBoolean(const QString &scope, const QString & key, bool val);

    ///
    /// \brief 设置整型值
    ///
    /// \author Johnny.Ren
    ///
    bool SetInteger(const QString &scope, const QString & key, int val);

    ///
    /// \brief 设置无符号长整型值
    ///
    /// \author Johnny.Ren
    ///
    bool SetULongLong(const QString& scope, const QString& key, qulonglong& val);

    ///
    /// \brief 设置无符号整数型
    ///
    /// \author Johnny.Ren
    ///
    bool SetUInteger(const QString &scope, const QString & key, unsigned int &val);

    ///
    /// \brief 设置浮点数
    ///
    /// \author Johnny.Ren
    ///
    bool SetDouble(const QString &scope, const QString & key, double val);

    ///
    /// \brief 设置字符串
    ///
    /// \author Johnny.Ren
    ///
    bool SetString(const QString &scope, const QString & key, const QString &val);

    ///
    /// \brief 新建一个范围
    ///
    /// \author Johnny.Ren
    ///
    bool NewScope(const QString &scope, const QVector<QVariant::Type>& types = QVector<QVariant::Type>());

    ///
    /// \brief 删除
    ///
    /// \author Johnny.Ren
    ///
    bool DelScope(const QString &scope);

	///
	/// \brief 删除字段
	///
	/// \author Johnny.Ren
	///
	bool DelValue(const QString &scope, const QString &key);

    ///
    /// \brief 设置变量
    ///
    /// \Param key 键
    /// \Param sVal 值
    /// \Param bStorage [in,out] 是否保存保存失败该值被置为false
    ///
    /// \author Johnny.Ren
    ///
    bool Set(const QString &key, const QVariant& val);

    ///
    /// \brief 获取变量
    ///
    /// \Param key 键值
    ///
    /// \author Johnny.Ren
    ///
    bool Get(const QString &key, QVariant &val);
};

Q_DECLARE_METATYPE(QLocalStorage::theSqliteFile::stTableInfo_t);
///
/// \brief 单元测试代码
///
/// \author Johnny.Ren
///
NGLBASE_EXPORT void q_local_storage_test();

#endif
