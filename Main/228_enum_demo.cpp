/*================================================================
*   Copyright (C) 2020 Renleilei. All rights reserved.
*   
*   文件名称：228_enum_demo.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2020年03月08日
*   描    述：
*   版    本: Version 1.00
================================================================*/

#include <iostream>

using namespace std;

enum Code {
	Code_A = 11,
	Code_B = 99,
};

int main()
{
	int a = 99;
	switch (a) {
	case Code_A:
		cout << "Code_A be called!" << endl;
		break;
	case Code_B:
		cout << "Code_B be called!" << endl;
		break;
	default:
		cout << "nothing be called!" << endl;
		break;
	}

	return 0;
}
