/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：184_test_long_long.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年08月29日
*   描    述：测试c++11对新的整型的定义
*   版    本: Version 1.00
================================================================*/

/*
	总结:
		- `C99`将其引入标准C，`C++11`将其引入标准C++
		- 在32位系统上, 一个`long long int`至少保有64位有效比特位
*/

#include <iostream>
#include <climits>		// #define LLONG_MIN & LLONG_MAX & ULLONG_MAX

using namespace std;

int main()
{
	long long int lli1 = -900000000000LL;
	unsigned long long int ulli1 = 900000000000000000ULL;
	cout << "lli1: " << lli1 << endl;						// -900000000000
	cout << "ulli1: " << ulli1 << endl;						// 900000000000000000
	cout << "LLONG_MIN: " << LLONG_MIN << endl;				// -9223372036854775808
	cout << "LLONG_MAX: " << LLONG_MAX << endl;				// 9223372036854775807
	cout << "ULLONG_MAX: " << ULLONG_MAX << endl;			// 18446744073709551615
	return 0;
}

