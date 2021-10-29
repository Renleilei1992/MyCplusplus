/*================================================================
*   Copyright (C) 2018 Renleilei. All rights reserved.
*   
*   文件名称：067_lambda.cpp
*   创 建 者：Renleilei (renleilei@foxmail.com)
*   创建日期：2018年07月05日
*   描    述：
*   版    本: Version 1.00
================================================================*/

#include <iostream>

using namespace std;

void testLambdaRefFunc();

int main(int argc, char **argv)
{

	int num_01 = 5;

	// lambda
	auto lambda_func = [](int x){ cout << "hello world! hello lambda!! x = [" << x << "]" <<endl; };

	void(*func)(int) = lambda_func;

	func(num_01);

	void(*func_01)(int) = lambda_func;
	func_01(num_01);

	testLambdaRefFunc();

	return 0;
}

void testLambdaRefFunc()
{
	// 情况1, 通过引用捕获
	int val = 10;
	auto func1 = [&val](){
		val++;
		std::cout << __func__ << " func1 be called! val: " << val << std::endl;
	};
	func1();
	std::cout << __func__ << "[1] val: " << val << std::endl;

	// 情况2, 通过参数列表传入引用
	val = 10;
	auto func2 = [](int& value){
		value++;
		std::cout << __func__ << " func2 be called! val: " << value << std::endl;
	};
	func2(val);
	std::cout << __func__ << "[2] val: " << val << std::endl;

	// 结果证明通过引用捕获变量或者通过参数列表传入引用都能实现修改局部变量的功能

	return;
}
