/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：176_test_bind.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年08月21日
*   描    述：c++11 新特性之 std::bind
*   版    本: Version 1.00
================================================================*/

#include <iostream>
#include <functional>

using namespace std;

struct Foo {
	void print_sum(int n1, int n2) {
		cout << __func__ << " " << n1 + n2 << endl;
	}

	int data = 10;
};

void print(int i, int j);

int main()
{
	using namespace std::placeholders;		// for _1, _2, _3
	
	auto f1 = std::bind([](int i, int j) { cout << __func__ << " i+j= " << i+j << endl;}, _1, _2);
	f1(99, 98);		// operator() i+j= 197

	auto f2 = std::bind(print, _1, _2);
	f2(66, 88);	

	Foo foo;
	auto f3 = std::bind(&Foo::data, _1);
	cout << __func__ << " " << f3(foo) << endl;
	auto f4 = std::bind(&Foo::print_sum, &foo, 99, _1);
	f4(1);

	return 0;
}


void print(int i, int j)
{
	cout << "i: " << i << " j: " << j << endl;
}
