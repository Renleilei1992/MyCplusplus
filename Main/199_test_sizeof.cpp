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

void funcImpl(const char* s) {
	cout << __func__ << ":s = [" << s << "]" << endl;
}

template<typename...Args>
void funcImpl(const char* s, Args...args) {
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

	funcImpl(args...);
}

int main()
{
	funcImpl_1("hello");
	funcImpl_1("hello", " world");
	funcImpl_1("hello", " world", "!");
	funcImpl_1("hello", " world", "!", "hello", " C", "++");
	funcImpl_1("hello", " world", "!", "hello", " C", "++", "!");

	return 0;
}
