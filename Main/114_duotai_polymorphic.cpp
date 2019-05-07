/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：114_duotai_polymorphic.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年05月05日
*   描    述：浅显展示C++多态的一个使用
*   版    本: Version 1.00
*   编译指令: g++ -o main 114_duotai_polymorphic.cpp -std=c++11
================================================================*/

#include <iostream>

using namespace std;

class Base
{
public:
	Base() { cout << "I'm the base class, construction func be called...\n"; }
	~Base() { cout << "I'm the base class, deconstruction func be called...\n"; }

	virtual void print() { cout << "Base::print()\n"; }
};

class Derived_1 : public Base
{
public:
	Derived_1() { cout << "I'm the derived_1 class, construction func be called...\n"; }
	~Derived_1() { cout << "I'm the derived_1 class, deconstruction func be called...\n"; }

	virtual void print() { cout << "Derived_1::print()\n"; }
};

class Derived_2 : public Base
{
public:
	Derived_2() { cout << "I'm the derived_2 class, construction func be called...\n"; }
	~Derived_2() { cout << "I'm the derived_2 class, deconstruction func be called...\n"; }

	virtual void print() { cout << "Derived_2::print()\n"; }
};

// 多态的业务常用方式之一, 利用基类指针来调用派生类重写的函数方法(推荐使用参数列表的引用????)
// 引用和指针异同点:
// 相同点: 1, 都是地址的概念(指针指向一块内存,它的内容是所指内存的地址;引用则是某块内存的别名)
// 不同点:
// 			1, 指针是一个实体, 而引用是一个别名;
//			2, 引用只能在定义时被初始化一次,之后不可变; 指针可能会被修改;(注意歧义)
//			3, 引用没有const, 指针有const, const的指针不能改变;(是指没有int& const a这种形式,有const int& a, 前者是指引用本身即别名不可被改变)
//			4, 引用不能为空, 指针可以为空;
//			5, sizeof(引用)得到的是所指向的对象的大小, sizeof(指针)得到的是指针本身的大小;	???
//			6, 指针和引用的自增(++)运算意义不同;
//			7, 引用是类型安全的,指针不是;
//			8, 是否C语言中对引用和指针有区别? 不支持引用??
void printlin(Base *p)
{
	if (nullptr != p) {
		cout << "----> 指针方式使用多态: sizeof(p) = " << sizeof(p) << " ";
		p->print();
	}
}

void printlin(Base &r)
{
	cout << "----> 引用方式使用多态: sizeof(r) = " << sizeof(r) << " ";
	r.print();
}

int main()
{
	// -------------------------------------------
	// 1.
	Base *b = new Base();
	b->print();
	delete b;
	b = nullptr;

	// 2. 
	Base b1;
	b1.print();

	// 3.
	Derived_1 d1;
	Derived_2 d2;
	Base *B = &b1;
	B->print();
	cout << "----- 多态 01 -----" << endl;
	B = &d1;
	B->print();
	cout << "----- 多态 02 -----" << endl;
	B = &d2;
	B->print();
	// -------------------------------------------

	
	// -------------------------------------------
	cout << "------ 多态例子展示另一形态 ------" << endl;
	cout << "--- 多态基类 ---" << endl;
	printlin(&b1);
	printlin(b1);
	cout << "--- 多态派生类 01 ---" << endl;
	printlin(&d1);
	printlin(d1);
	cout << "--- 多态派生类 02 ---" << endl;
	printlin(&d2);
	printlin(d2);
	return 0;
}
