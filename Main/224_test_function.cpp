/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：224_test_function.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年12月12日
*   描    述：简单测试C++11的 function 类模板
*   版    本: Version 1.00
================================================================*/

#include <iostream>
#include <map>
#include <functional>		// std::function
#include <string>

using namespace std;
using namespace std::placeholders;		// _1 _2

// 加法函数
int add(int op1, int op2) {
	return op1 + op2;
}

// 减法 lambda表达式
auto minus_op = [](int op1, int op2) { return op1 - op2; };

// 函数对象
struct multiply_op {
	int operator()(int op1, int op2) {
		return op1 * op2;
	}
};

// 除法函数
int devide(int op1, int op2, bool check0) {
	if (check0 && (op2 == 0)) {
		return 0;
	}

	return op1 / op2;
}

// 参数绑定
auto dev_op = bind(devide, _1, _2, false);

// 自定义算法
auto diy_op = std::bind([](int op1, int op2) -> int { return op1 * op2 + 1000000; }, _1, _2);

int main()
{
	std::map<string, std::function<int(int, int)>> op = {
		{"+", add},
		{"-", minus_op},
		{"*", multiply_op()},
		{"/", dev_op},
		{"diy", diy_op},
	};

	cout << "测试加法: " << op["+"](1, 2) << endl;
	cout << "测试减法: " << op["-"](3, 4) << endl;
	cout << "测试乘法: " << op["*"](5, 6) << endl;
	cout << "测试除法: " << op["/"](7, 8) << endl;
	cout << "测试自定义算法: " << op["diy"](100, 999) << endl;

	return 0;
}
