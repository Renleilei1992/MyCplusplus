/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：202_test_move.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年10月22日
*   描    述：简单使用std::move
*   版    本: Version 1.00
================================================================*/

#include <iostream>
#include <utility>
#include <string>
#include <vector>

using namespace std;

void move_copy();

int main()
{
	move_copy();

	return 0;
}

void move_copy()
{
	std::string str = "Hello";
	std::vector<std::string> vec;
	
	// 使用 push_back(const T&) 重载, 会带来复制 str 的成本
	vec.push_back(str);
	cout << __func__ << "::After copy, str is \"" << str << "\"" << endl;

	// 使用右值引用 push_back(T&&) 重载, 表示不会复制str字符串, 而是将 str 的内容移动至 vector, 开销会低于复制, 原str可能为空
	vec.push_back(std::move(str));
	cout << __func__ << "::After move, str is \"" << str << "\"" << endl;
	
	cout << "The contents of the vector are \"" << vec[0] << "\", \"" << vec[1] << "\"" << endl;
}
