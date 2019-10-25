/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：203_text_explicit.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年10月25日
*   描    述：explicit说明符的c++11新特性简单测试
*   版    本: Version 1.00
*   编译指令: g++ -o main 203_text_explicit.cpp -std=c++11
*   参考文献: https://zh.cppreference.com/w/cpp/language/converting_constructor
*             https://zh.cppreference.com/w/cpp/language/explicit
*             https://blog.csdn.net/craftsman1970/article/details/81209198
================================================================*/

/*
	转换构造函数: 不使用explicit说明符声明(且可以单个参数调用(C++11之前))的构造函数被称为转换构造函数;
	用途	    : 可以用于复制初始化,可能出现隐式类型转换
*/

#include <iostream>

using namespace std;

struct Base1
{
	Base1() { cout << "Base1:: 1" << __func__ << endl; }			// 转换构造函数 C++11 起
	Base1(int) { cout << "Base1:: 2" << __func__ << endl; }			// 转换构造函数 C++11之前
	Base1(int, int) { cout << "Base1:: 3" << __func__ << endl;}		// 转换构造函数 C++11 起
};


struct Base2
{
	explicit Base2() { cout << "Base2:: 1" << __func__ << endl; }
	explicit Base2(int) { cout << "Base2:: 2" << __func__ << endl; }
	explicit Base2(int, int) { cout << "Base2:: 3" << __func__ << endl;}
};
int main(int argc, char** argv)
{
	Base1 b1_0;					// Base1:: 1Base1
	Base1 b1_1 = 100;			// Base1:: 2Base1
	Base1 b1_2(200);			// Base1:: 2Base1
	Base1 b1_3{300, 400};		// Base1:: 3Base1
	Base1 b1_4 = {300, 400};	// Base1:: 3Base1
	Base1 b1_5 = (Base1)500;	// Base1:: 2Base1
	
	cout << "-------------------------" << endl;

	Base2 b2_0;					// Base2:: 1Base2
//	Base2 b2_1 = 100;			// conversion from ‘int’ to non-scalar type ‘Base2’ requested	隐式转换编译不通过
	Base2 b2_2(200);			// Base2:: 2Base2
	Base2 b2_3{300, 400};		// Base2:: 3Base2
//	Base2 b2_4 = {300, 400};	// converting to ‘Base2’ from initializer list would use explicit constructor ‘Base2::Base2(int, int)’  列表初始化的隐式转换编译不通过
	Base2 b2_5 = (Base2)500;	// Base2:: 2Base2	(显式转换)
	Base2 b2_6{};				// Base2:: 1Base2
//	Base2 b2_7 = {};			// converting to ‘Base2’ from initializer list would use explicit constructor ‘Base2::Base2()’	列表初始化的隐式转换编译不通过
	Base2 b2_8 = static_cast<Base2>(600);	// Base2:: 2Base2   (显式转换)

	return 0;
}
