/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：109_singleton.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年04月28日
*   描    述：梳理单例模式
*   版    本: Version 1.00
================================================================*/

#include <iostream>

using namespace std;

// *************************************************************************
// lazy singleton
class Singleton_lazy
{
private:
	Singleton_lazy() { cout << "Singleton_lazy's construction func be called..." << endl; }
	~Singleton_lazy() { cout << "Singleton_lazy's deconstruction func be called..." << endl; }
	//Singleton_lazy(const Singleton_lazy&);
	//Singleton_lazy& operator=(const Singleto_lazy&);

public:
	static Singleton_lazy* getInstance() {
		 if (NULL == m_instance) {
			m_instance = new Singleton_lazy;
		 }
		
		 cout << "m_instance's addr: " << m_instance << endl;
		return m_instance;
	}

private:
	static Singleton_lazy* m_instance;

// 附加一个可以避免内存泄漏的方法
private:
	// class AutoDeletor {
	// public:
	// 	AutoDeletor() { cout << "AutoDeletor's construction func be called!!" << endl; }
	// 	~AutoDeletor() {
	// 		cout << "AutoDeletor's deconstruction func be called!" << endl;
	// 		if (Singleton_lazy::m_instance != NULL) {
	// 			delete Singleton_lazy::m_instance;
	// 			Singleton_lazy::m_instance = NULL;	// delete之后变野指针,置空
	// 		}
	// 	}
	// };

	// static AutoDeletor deletor;		// 程序结束时会自动释放全局变量,释放此变量时触发析构函数来delete申请的内存

};

Singleton_lazy* Singleton_lazy::m_instance = NULL;
// **************************************************************************


// **************************************************************************
// Meyer's singleton (在C++11标准下是线程安全的,此单例模式会自动在程序结束时释放资源)
class Singleton_Meyer
{
private:
	
}

// **************************************************************************

int main(int argc, char **argv)
{
	cout << "-------懒汉式单例模式开启---------" << endl;
	Singleton_lazy* p1 = Singleton_lazy::getInstance();
	Singleton_lazy* p2 = Singleton_lazy::getInstance();

	cout << "p1'addr: " << p1 << endl;
	cout << "p2'addr: " << p2 << endl;
	//delete p1;	// 会报编译错误，析构函数是私有的
	//delete p2;
	cout << "-------懒汉式单例模式结束---------" << endl;


	cout << "-------饿汉式单例模式开启---------" << endl;

	cout << "-------饿汉式单例模式结束---------" << endl;


	cout << "-------Meyer's 单例模式开启---------" << endl;
	cout << "-------Meyer's 单例模式结束---------" << endl;
	return 0;
}
