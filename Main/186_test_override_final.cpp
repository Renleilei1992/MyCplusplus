/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：186_test_override_final.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年08月29日
*   描    述：简要测试一下C++11的override和final 保留字
*   版    本: Version 1.00
================================================================*/

/*
	总结:
		1, final将禁止继承和禁止基类虚函数重写
		2, override 保留字可以提醒此函数是重写的基类虚函数; 强制编译器检查是否重写了基类的虚函数,校验函数名和参数是否相同
*/

#include <iostream>

using namespace std;

class Base
{
public:
	virtual void basePrint() = 0;
	virtual void basePrint1() = 0;
	virtual void basePrint2() final { cout << __func__ << " Base: " << endl; }
};

class Split : public Base
{
	// 隔离接口
};

class Derived final : public Split
{
public:
	virtual void basePrint() override { cout << __func__ << " Derived: " << endl; }
	virtual void basePrint1() override { cout << __func__ << " Derived: " << endl; }
//	virtual void basePrint2() override { cout << __func__ << " Derived: " << endl; }		// final会导致此处继承编译出现错误
};

//class Derived1 : public Derived		// cannot derive from ‘final’ base ‘Derived’ in derived type ‘Derived1’
//{
//};

int main()
{
	Derived d1;
	d1.basePrint();		// basePrint Derived:
	d1.basePrint1();	// basePrint1 Derived:
	d1.basePrint2();	// basePrint2 Base:

	return 0;
}
