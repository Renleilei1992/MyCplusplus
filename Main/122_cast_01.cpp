/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：122_cast_01.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年05月07日
*   描    述：
*   版    本: Version 1.00
================================================================*/

#include <cstdlib>
#include <cstdio>
#include <iostream>

using namespace std;

int check()
{
	union UN
	{
		int n;
		char c;
	}un;
	un.n = 1;
	cout << "check terminal is bigendian or smallendian un.c: " << un.c << endl;
	return un.c;
}

int main()
{
	int i = 8;
	char *c = (char*)&i;

	cout << "c[0]: " << (int)c[0] << endl;
	cout << "c[1]: " << (int)c[1] << endl;
	cout << "c[2]: " << (int)c[2] << endl;
	cout << "c[3]: " << (int)c[3] << endl;
//	cout << "c[4]: " << (int)c[4] << endl;

	if ((int)c[0] == i) {
		cout << "小端" << endl;
	} else {
		cout << "大端" << endl;
	}

	// 第二个方法判断大小端
	if (check()) {
		cout << "小端" << endl;
	} else {
		cout << "大端" << endl;
	}
	return 0;
}
