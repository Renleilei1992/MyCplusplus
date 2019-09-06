/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：171_constexpr.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年08月20日
*   描    述：
*   版    本: Version 1.00
*	编译指令: g++ -o main 171_constexpr.cpp -std=c++11
*	参考文献: https://zh.cppreference.com/w/cpp/language/constexpr
*			  https://www.zhihu.com/question/35614219/answer/63798713
================================================================*/

/*
总结:
		1, constexpr 修饰常量表达式 const 修饰常量
		2, constexpr 修饰的常量表达式限定在了编译期常量,(返回值不一定时编译期常量)
			- constexpr 修饰的函数:
				 1,如果传入的参数可以在编译时期计算出来,那么这个函数就会产生编译时期的值,
				 2,如果传入的参数在编译时期不能计算出来,那么constexpr修饰的函数就和普通的函数一致
		3, 如何确定constexpr修饰的函数是否产生编译时期的值?
			- 可以使用std::array 需要编译器常值才能编译通过的小技巧,这样可以检测是否产生编译期常值
			- 合理使用constexpr修饰常量表达式用以帮助编译器优化代码
*/

#include <iostream>
#include <array>

using namespace std;

void test_constexpr();
void test_constexpr2();
constexpr int foo(int i);

int main()
{
	test_constexpr();
	test_constexpr2();
	return 0;
}


void test_constexpr()
{
	cout << __func__ << endl;
//	int i = 10;					// error: the value of ‘i’ is not usable in a constant expression
	const int i = 10;
	constexpr int j = i + 20;
	cout << "i = " << i << " j = " << j << endl;
}

constexpr int foo(int i)
{
	return i + 5;
}

void test_constexpr2()
{
	cout << __func__ << endl;
	int i = 10;
	std::array<int, foo(5)> arr;		// ok

	foo(i);								// ok

	// But..
	std::array<int, foo(i)> arr1;		// Error: ‘int i’ is not const
}

