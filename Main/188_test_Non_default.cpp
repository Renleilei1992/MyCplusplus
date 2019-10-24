/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：188_test_Non_default.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年08月29日
*   描    述：测试c++11使用和禁用对象的默认函数
*   版    本: Version 1.00
*   编译指令: g++ -o main 188_test_Non_default.cpp -std=c++11
================================================================*/

#include <iostream>

using namespace std;

class Base1
{
public:
	Base1() = default;		// 显式声明需要默认构造函数
	~Base1() = default;

	virtual void print() final { cout << "Base1::" << __func__ << endl; }
};

class NonCopyAble
{
public:
	NonCopyAble & operator=(const NonCopyAble&) = delete;
	NonCopyAble(const NonCopyAble&) = delete;
	NonCopyAble() = default;

	void print() { cout << "NonCopyAble::" << __func__ << endl; }
};

class NonNewAble
{
public:
	NonNewAble() = default;
	void *operator new(std::size_t) = delete;	// 禁止类使用new申请内存, 此种对象只能生成于stack栈中,无法直接配置于heap堆中
	void print() { cout << "NonNewAble::" << __func__ << endl; }
};

struct NonDouble
{
	void foo(int i) { cout << "NonDouble::" << __func__ << " i = " << i << endl; }
	void foo(double i) = delete;
};

struct OnlyInt
{
	void foo(int i) { cout << "OnlyInt::" << __func__ << " i = " << i << endl; }
	template<class T> void foo(T) = delete;
};

class Sub/*: public NonCopyAble*/
{
public:
	Sub() {
		cout << "Sub::" << __func__ << endl;
	}
/*	Sub(const Sub& rhs):NonCopyAble(rhs){
		cout << "Sub::" << __func__ << endl;
	}
*/
};

int main()
{
	/* 测试禁止new申请堆内存的类 */
//	NonNewAble *nPtr = new NonNewAble();		// use of deleted function ‘static void* NonNewAble::operator new(std::size_t)’
//	if (nPtr == nullptr) { cout << "it's a nullptr!!" << endl; }
	NonNewAble nObj;
	nObj.print();

	/* 测试禁止拷贝构造的类 */
	NonCopyAble copyObj;
//	NonCopyAble c1(copyObj);	// error: use of deleted function ‘NonCopyAble::NonCopyAble(const NonCopyAble&)’
	NonCopyAble c2;
//	c2 = copyObj;				// error: use of deleted function ‘NonCopyAble& NonCopyAble::operator=(const NonCopyAble&)’
	copyObj.print();
//	c1.print();
//	c2.print()

	/* 测试禁止double形参的类 */
	NonDouble ndObj;
	int i = 10;
	double j = 20;
	ndObj.foo(i);
//	ndObj.foo(j);	// error: use of deleted function ‘void NonDouble::foo(double)’

	/* 测试仅使用int形参的类 */
	OnlyInt iObj;
	iObj.foo(i);
//	iObj.foo(j);	// error: use of deleted function ‘void OnlyInt::foo(T) [with T = double]’

	Sub subObj_1;
	Sub subObj_2(subObj_2);		// error: use of deleted function ‘Sub::Sub(const Sub&)’ [if you public NonCopyAble]

	return 0;
}
