/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：220_inherit_use_1.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年12月05日
*   描    述：简单使用公有、保护、私有继承
*   版    本: Version 1.00
*   参考链接: [C++之共有继承、保护继承、私有继承](https://www.cnblogs.com/weiyouqing/p/9648563.html)
================================================================*/

/*

*/

#include <iostream>
using namespace std;

class A
{
public:
	int a = 0;
	virtual void fun() {
		cout << "A::a: " << a << endl;
		cout << "A::a1: " << a1 << endl;
		cout << "A::a2: " << a2 << endl;
		cout << "A::a3: " << a3 << endl;
	}
public:
	int a1 = 1;
protected:
	int a2 = 2;
private:
	int a3 = 3;
};


// 公有继承: 
// 基类成员属性  |  继承方式  |  派生类成员访问属性
// private成员   |            |    无法访问
// protected成员 |   public   |    protected
// public成员    |            |    public
class A1 : public A
{
public:
	virtual void fun() {
		cout << "A1::a: " << a << endl;
		cout << "A1::a1: " << a1 << endl;	// 基类的public成员, 派生类中仍然是public成员
		cout << "A1::a2: " << a2 << endl;	// 基类的protected成员, 派生类中仍然是protected, 可以被派生类访问
	//	cout << "A1::a3: " << a3 << endl;	// 基类的private成员, 派生类中无法访问
	}
};

// 保护继承: 
// 基类成员属性  |  继承方式  |  派生类成员访问属性
// private成员   |            |    无法访问
// protected成员 | protected  |    protected
// public成员    |            |    protected
class A2 : protected A
{
public:
	virtual void fun() {
		cout << "A2::a: " << a << endl;		// 基类的public成员, 派生类中变为protected成员, 可以被派生类访问
		cout << "A2::a1: " << a1 << endl;	// 基类的public成员, 派生类中变为protected成员, 可以被派生类访问
		cout << "A2::a2: " << a2 << endl;	// 基类的protected成员, 派生类中仍为为protected成员, 可以被派生类访问
	//	cout << "A2::a3: " << a3 << endl;	// 基类的private成员, 派生类中无法访问
	}
};


// 私有继承: 
// 基类成员属性  |  继承方式  |  派生类成员访问属性
// private成员   |            |    无法访问
// protected成员 |  private   |    private
// public成员    |            |    private
class A3 : private A
{
public:
	virtual void fun() {
		cout << "A3::a: " << a << endl;		// 基类的public成员, 派生类中变为private成员, 可以被派生类访问
		cout << "A3::a1: " << a1 << endl;	// 基类的public成员, 派生类中变为private成员, 可以被派生类访问
		cout << "A3::a2: " << a2 << endl;	// 基类的protected成员, 派生类中变为private成员, 可以被派生类访问
	//	cout << "A3::a3: " << a3 << endl;	// 基类的private成员, 派生类中无法访问
	}
};


int main()
{
	A a;
	a.fun();

	cout << "-------------公有继承----------------" << endl;
	A1 a1;
	cout << "类外访问基类成员变量: a " <<  a1.a << endl;
	cout << "类外访问基类成员变量: a1 " <<  a1.a1 << endl;
	//cout << "类外访问基类成员变量: a2 " <<  a1.a2 << endl;
	//cout << "类外访问基类成员变量: a3 " <<  a1.a3 << endl;
	a1.fun();

	cout << "-------------保护继承----------------" << endl;
	A2 a2;
	//cout << "类外访问基类成员变量: a " <<  a2.a << endl;
	//cout << "类外访问基类成员变量: a1 " <<  a2.a1 << endl;
	//cout << "类外访问基类成员变量: a2 " <<  a2.a2 << endl;
	//cout << "类外访问基类成员变量: a3 " <<  a2.a3 << endl;
	a2.fun();

	cout << "-------------私有继承----------------" << endl;
	A3 a3;
	//cout << "类外访问基类成员变量: a " <<  a3.a << endl;
	//cout << "类外访问基类成员变量: a1 " <<  a3.a1 << endl;
	//cout << "类外访问基类成员变量: a2 " <<  a3.a2 << endl;
	//cout << "类外访问基类成员变量: a3 " <<  a3.a3 << endl;
	a3.fun();
	return 0;
}
