/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：205_test_limitReferenceQualifier.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年10月25日
*   描    述：对C++11新特性中的引用限定符
*   版    本: Version 1.00
*   参考文献: [C++11左值、右值、右值引用详解](https://blog.csdn.net/hyman_yx/article/details/52044632)
================================================================*/

/*
	前置知识: (C++11)
		- 左值: 可以取地址,有名字的是左值;
		- 右值: 不可以取地址,没有名字的是右值(将亡值或者纯右值)
*/


#include <iostream>

using namespace std;

struct X {
	void foo() & {	// 引用限定符 &, 表明this对象指向着左值对象
		cout << "X:: 1 " << __func__ << endl;
	}
	void foo() && {	// 引用限定符 &&, 表明this对象指向着右值对象
		cout << "X:: 2 " << __func__ << endl;
	}
};

void getValue(int& i)
{
	cout << __func__ << "::LValue " << i << endl;
}

void getValue(int&& i)
{
	cout << __func__ << "::RValue " << i << endl;
}

int main()
{
	X x;
	x.foo();	// X:: 1
	X().foo();	// X:: 2

	X *x_ptr = new X();
	x_ptr->foo();
	delete x_ptr;

	cout << "--------------------------" << endl;
	int a = 0;					// 局部变量 a 为左值; 非常量左值
	int&& b = 1;				// b 为右值引用, 但是b有名字, 此处被视为左值
	int&& c = std::move(b);
//	int &d = 3;					// invalid initialization of non-const reference of type ‘int&’ from an rvalue of type ‘int’ 左值引用绑定到右值,编译失败
	getValue(a);				// LValue 0
	getValue(2);				// RValue 2
	getValue(b);				// LValue 1
	getValue(c);				// LValue 1

	return 0;
}
