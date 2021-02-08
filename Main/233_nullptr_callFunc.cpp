/*================================================================
*   Copyright (C) 2020 Renleilei. All rights reserved.
*   
*   文件名称：233_nullptr_callFunc.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2020年05月22日
*   描    述：测试空指针访问成员函数与虚函数的不同场景
*   版    本: Version 1.00
================================================================*/

#include <iostream>

using namespace std;

class A {
public:
	void f() {}
	virtual void f1() {}
	void f2() {
		m_data++;
	}

private:
	int m_data = 0;
};

int main()
{
	A* a = nullptr;
	a->f();		// 不会崩溃, 原因是访问成员函数地址是通过静态编译获取的函数地址, 相当于编译器认为是调用的 A::f(this)
	//a->f1();	// 会崩溃, 原因是动态联编,运行时会根据动态类型去访问虚表, 访问虚函数需要通过虚函数表去找到虚函数的地址, 
	a->f2();	// 会崩溃, 原因是调用 A::f2(this) { this->m_data++; } 其中this==nullptr
	return 0;
}
