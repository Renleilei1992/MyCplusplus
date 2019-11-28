/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：216_get_Gcd.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年11月22日
*   描    述：2行代码求最大公因数
*   版    本: Version 1.00
================================================================*/

#include <iostream>
#include <chrono>

using namespace std;

int gcd(int x, int y);
long long gcd(long long x, long long y);

int main()
{
	int x = 5505;
	int y = 1100;
	auto start = std::chrono::high_resolution_clock::now();
	cout << "最大公因数: x: " <<  x << " y: " << y << " result: " << gcd(x, y) << endl;
	auto end = std::chrono::high_resolution_clock::now();
	cout << "usage time: " << std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(end -start).count() << endl;
	

	long long a = 6362246400000000;
	long long b = 7779171692000000;
	auto start_1 = std::chrono::high_resolution_clock::now();
	cout << "最大公因数: a: " <<  a << " b: " << b << " result: " << gcd(a, b) << endl;
	auto end_1 = std::chrono::high_resolution_clock::now();
	cout << "usage time: " << std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(end_1 -start_1).count() << endl;

	return 0;
}

int gcd(int x, int y)
{
	return y ? gcd(y, x%y) : x;
}

long long gcd(long long x, long long y)
{
	return x % y == 0 ? y : gcd(y, x%y);
	//return y ? gcd(y, x%y) : x;
}
