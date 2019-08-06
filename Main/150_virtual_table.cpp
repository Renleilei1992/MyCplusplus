/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：150_virtual_table.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年08月02日
*   描    述：
*   版    本: Version 1.00
================================================================*/

#include <iostream>

using namespace std;

class A
{

public:
	virtual void A_func1(){ cout << "A_func1() be called!!" << endl; }
	virtual void A_func2(){ cout << "A_func2() be called!!" << endl; }
};

class B : public A
{
public:
	virtual void A_func1() { cout << "B class: A_func1() be called!!" << endl; }
};


int main()
{
	A a;
	B b;

	a.A_func1();
	b.A_func1();
	b.A_func2();

	return 0;
}
