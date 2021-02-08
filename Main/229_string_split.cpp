/*================================================================
*   Copyright (C) 2020 Renleilei. All rights reserved.
*   
*   文件名称：229_string_split.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2020年03月19日
*   描    述：使用正则库进行字符串替换
*   版    本: Version 1.00
================================================================*/

#include <iostream>
#include <string>
#include <regex>

using namespace std;

// 方法1: 使用正则表达式(需要C++11支持,引入正则库)
void split_planA(const std::string sourceStr);

int main()
{
	const std::string str = "abc def";

	// test plan A
	split_planA(str);

	return 0;
}

void split_planA(const std::string sourceStr)
{
	std::regex ws_re("\\s+");	// 空格
	std::vector<std::string> vec(std::sregex_token_iterator(sourceStr.begin(), sourceStr.end(), ws_re, -1), std::sregex_token_iterator());

	for (auto&& s : vec) {
		cout << s << endl;
	}
}
