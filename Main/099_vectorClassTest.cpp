/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：099_vectorClassTest.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年03月26日
*   描    述：
*   版    本: Version 1.00
================================================================*/

#include "../include/vectorClassTest.h"

/*
#include <iostream>
#include <string.h>
#include <vector>

using namespace std;
*/

int main()
{
	int iRet = 100;
	std::vector<std::string> vec_01;
	vec_01.push_back("hello world");

	for (auto iVec : vec_01) {
		cout << iVec << endl;
	}

/*
	VectorTest* vecClass = new VectorTest();
	if (vecClass) {
		vecClass->insertContent(&vec_01, &iRet);
	};
*/
	VectorTest vecClass(iRet);

	for (auto iVec : vec_01) {
		cout << iVec << endl;
	}
	cout << iRet << endl;

	return 0;
}
