/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：204_test_noexcept.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年10月25日
*   描    述：简单测试 noexcept c++11
*   版    本: Version 1.00
================================================================*/

#include <iostream>
#include <stdexcept>	// runtime_error

using namespace std;

class Tracer
{
public:
	Tracer() {}
	Tracer(const char* str):m_str(str) {}

	Tracer(Tracer& t):m_str(t.m_str) { throw runtime_error("copy exception!"); }
	Tracer(Tracer&& t) noexcept :m_str(std::move(t.m_str)) { throw runtime_error("move exception!"); }

private:
	string m_str;
};


int main()
{
	Tracer t("hello world!");

	// 测试拷贝构造函数抛出异常
	try {
		Tracer t1 = t;
	} catch (runtime_error e) {
		cout << "1 catch!! error: " << e.what() << endl;
	}

	// 测试使用了 noexcept 的移动构造函数是否会抛出异常
	try {
		Tracer t2 = std::move(t);
	} catch (runtime_error e) {
		cout << "2 catch!! error: " << e.what() << endl;
	}
	return 0;
}
