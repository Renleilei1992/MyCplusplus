/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：185_test_static_assert.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年08月29日
*   描    述：
*   版    本: Version 1.00
================================================================*/

#include <iostream>

using namespace std;

int main()
{
	int a = 10;
	char b = 'c';
	static_assert(sizeof(a) == sizeof(b), "a size != b size !!");
	cout << "program end!" << endl;

	return 0;
}
