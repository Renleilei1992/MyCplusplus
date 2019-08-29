/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：180_test_rawString.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年08月23日
*   描    述：字符串字面值, c++11提供raw原始字符串字面值
*   版    本: Version 1.00
================================================================*/

#include <iostream>
#include <cstring>

using namespace std;

int main()
{
	std::string str1 = R"(The String Data \ Stuff")";	// The String Data \ Stuff"   在括号中得字符串将不再需要转义即可正确展示

	cout << str1 << endl;

	std::string str2 = R"(The String Dat
						a \ Stuff")";
	cout << str2 << endl;

	return 0;
}
