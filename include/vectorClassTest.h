/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：vectorClassTest.h
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年03月26日
*   描    述：
*   版    本: Version 1.00
================================================================*/


#pragma once
#ifndef VECTORCLASSTEST_H
#define VECTORCLASSTEST_H
#include <vector>
#include <string.h>
#include <iostream>

using namespace std;

class VectorTest
{
public:
	VectorTest(int i){ cout << "construct: " << i <<endl; };

public:
	int setOption(vector<std::string>* pVecStr) { 
		if (pVecStr != NULL) {
		//	m_vec = pVecStr;
			return 0;
		} else {
			return -1;
		}	
	};

	void insertContent(vector<std::string>* pVecStr, int* pRetVal) {
		vector<std::string>* tempVec = pVecStr; 
		if (tempVec != NULL || pRetVal != NULL) {
			tempVec->push_back("hello C++");
			*pRetVal = 10000;
		}
	};

/*
	void printContent() {
		for (auto iVec : m_vec) {
			cout << iVec << endl;
		}
	};
*/
public:
//	vector<std::string>& m_vec;
};


#endif // VECTORCLASSTEST_H
