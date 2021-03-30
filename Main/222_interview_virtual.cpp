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
		6) 基类构造函数不能声明为virtual虚函数; (虚表建立时需要存储在对象内存空间内,但是构造函数是虚函数的话就需要先有虚表才能通过虚表调用虚函数创建对象, 对象没有实例化也意味着没有内存空间, 意味着没有虚表)
		7) 基类析构函数尽量使用virtual虚函数, 这样(Base* b2 = new Derived(); delete b2;)可以析构的时候先调用子类的析构函数再调用基类的析构函数,否则将只会调用基类的析构函数.
*/



#include <iostream>

using namespace std;


class Base
{
public:
	Base() { cout << "Base::" << __func__ << " ---> be called!" << endl; /*print();*/ }
	virtual ~Base() { cout << "Base::" << __func__ << " ---> be called!" << endl; /*show();*/ }
	
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
		/*print();*/
	}
	~Derived() { cout << "Derived::" << __func__ << " ---> be called!" << endl; /*show();*/ }
	
//	virtual void print() { cout << "Derived::" << __func__ << " ---> be called!" << endl; }
	void func() { cout << "Derived::" << __func__ << "---> be called!" << endl;}
};


int main()
{
//	Base b1;
//	Derived d1;
	Base* b2 = new Derived();
//	b2->func();	// 编译不通过, 基类指针只能调用虚函数.
	delete b2;

	// 会自增至 0->127 然后开始 -128->-1->0->127 不断循环.
//	for(char i = 0; i < 256; ++i) {
//    	printf("%d\n", i);
//	}

	return 0;
}
