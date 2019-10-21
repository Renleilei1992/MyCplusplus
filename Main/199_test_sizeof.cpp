/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：199_test_sizeof.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年10月18日
*   描    述：
*   版    本: Version 1.00
================================================================*/

#include <iostream>

using namespace std;

template<typename T>
void funcImpl(const T& s) {
	cout << s;
}

template<typename T,typename...Args>
void funcImpl(const T& s, Args...args) {
	funcImpl(s);
	funcImpl(args...);
}

template<typename...Args>
void funcImpl_1(Args...args) {
	const int arg_count = sizeof...(args);
	if (arg_count < 2 || arg_count > 5) {
		cout << __func__ << "::Arg count error! arg_count: " << arg_count << endl;
		return;
	}

	cout << __func__ << ": ";
	funcImpl(args...);
	cout << endl;
}

int main()
{
	int i = 2019;
	int j = 2020;
	funcImpl_1("hello");
	funcImpl_1("hello", " world");
	funcImpl_1("hello", " world", "!");
	funcImpl_1("hello", " world", "! ", i);
	funcImpl_1("hello", " world", "!", " hello ", j);
	funcImpl_1("hello", " world", "!", " hello", " C", "++", "!");

	return 0;
}
