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

int main(int argc, char **argv)
{

	int num_01 = 5;

	// lambda
	auto lambda_func = [](int x){ cout << "hello world! hello lambda!! x = [" << x << "]" <<endl; };

	void(*func)(int) = lambda_func;

	func(num_01);

	void(*func_01)(int) = lambda_func;
	func_01(num_01);

	return 0;
}
