/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：123_lambda_01.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年05月07日
*   描    述：C++11匿名函数的使用([ capture ] ( params ) mutable exception attribute -> ret { body })
*   版    本: Version 1.00
*   编译指令: g++ -o main 123_lambda_01.cpp -std=c++11
================================================================*/
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

void f1();
void f2();
void f3();

int main()
{
	int i = 999;
	auto lambda_func = [](int x){ cout << "hello world! hello lambda!! x = [" << x << "]" <<endl; };
	lambda_func(i);
    void(*func)(int) = lambda_func;
    func(i);

	// mutable 关键字用于 按值捕获 的场景,修改值不影响外部的值变化,使用了副本
	[](){ cout << "无法使用外部变量 i: " << i << endl; };
	[=]()mutable{ cout << "任何外部变量都隐式按值捕获: i: " << ++i << endl; };
	[&](){ cout << "任何外部变量都隐式按引用捕获: i: " << i << endl; };

	auto Min = [](int a, int b) -> int{ return a < b ? a : b; };
	cout << "Min of (7,10): " << Min(7,10) << endl;	

	/*
	// 编译未通过
	auto lambda_func1 = [](int x) -> int { int z = x + 1; return z; };
	void(*func1)(int) = lambda_func1;
	func1(i);
	*/

	f1();
	return 0;
}

void f1()
{
	std::vector<int> vec;
	int total = 0;
	for(int i = 0; i < 5; ++i) { vec.push_back(i); }

	for_each(begin(vec), end(vec), [&total](int x){
		cout << "begin: f1()::x: " << x << " total: "<< total << endl;
		total += x;
		cout << "end:   f1()::x: " << x << " total: "<< total << endl;
	});
}
