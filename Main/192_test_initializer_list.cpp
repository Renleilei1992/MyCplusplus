/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：192_test_initializer_list.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年09月04日
*   描    述：简单测试 C++11 的列表初始化模板类  initializer_list
*   版    本: Version 1.00
================================================================*/

#include <iostream>
#include <initializer_list>
#include <algorithm>		// for_each

using namespace std;

double sum(std::initializer_list<double> i1);
double average(const std::initializer_list<double> & ri1);

int main()
{
	cout << "program begin!!" << endl;
	cout << "List 1: sum = " << sum({1, 2, 3, 4}) << endl;
	return 0;
}

double sum(std::initializer_list<double> i1)
{
	double tot = 0;
/*
	for (auto p = i1.begin(); p != i1.end(); p++) {
		tot += *p;
	}
*/

	for_each(std::begin(i1), std::end(i1), [&](int p){
		tot += p;
	});

	return tot;
}
