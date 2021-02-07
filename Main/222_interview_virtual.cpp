/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：222_interview_virtual.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年12月05日
*   描    述：简单测试面试中会遇到的virtual虚函数问题
*   版    本: Version 1.00
================================================================*/

/*
	总结:
		1) 当基类构造函数中使用虚函数, 会正常调用该虚函数, 但是没有意义, 派生类不存在也不会有多态产生;
		2) 当子类构造函数中使用虚函数时, 如果子类未实现该虚函数则会调用基类的虚函数; else 调用自己实现的虚函数;
		3) 当基类析构函数中使用虚函数时, 由于子类对象已经被析构, 也不会有多态产生, 无意义;
		4) 当子类析构函数中使用虚函数时, 如果子类未实现该虚函数则会调用基类的虚函数; else 调用自己实现的虚函数;
		5) 基类的析构函数建议使用虚函数, 这样的话可以调用到子类的虚函数进行资源的释放; 5)和3)不同,3)是析构函数内调用,5)是 virtual ~A();
*/



#include <iostream>

using namespace std;


class Base
{
public:
	Base() { cout << "Base::" << __func__ << " ---> be called!" << endl; print(); }
	~Base() { cout << "Base::" << __func__ << " ---> be called!" << endl; show(); }
	
	virtual void print() { cout << "Base::" << __func__ << " ---> be called! m_base: " << m_base << endl; }
	virtual void show() { cout << "Base::" << __func__ << " ---> be called! m_base: " << m_base << endl; }
private:
	int m_base;
};

class Derived : public Base
{
public:
	explicit Derived() {
		cout << "Derived::" << __func__ << " ---> be called!" << endl;
		print();
	}
	~Derived() { cout << "Derived::" << __func__ << " ---> be called!" << endl; show(); }
	
//	virtual void print() { cout << "Derived::" << __func__ << " ---> be called!" << endl; }
};


int main()
{
//	Base b1;
	Derived d1;

	return 0;
}
