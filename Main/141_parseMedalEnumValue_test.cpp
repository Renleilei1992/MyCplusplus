/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：141_parseMedalEnumValue_test.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年07月01日
*   描    述：
*   版    本: Version 1.00
================================================================*/

#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <cstring>
using namespace std;

int main()
{
	std::vector<double> tempVec;
	std::map<double, std::string> tempMap;
	int uValue = 34352;
	std::string strVal = "hello";
	for(int i = 0; i < 32; ++i) {
		if((uValue >> i & 1) == 0) {
			tempVec.push_back(pow(2, i));
			//tempMap.insert(std::make_pair(pow(2, i), strVal));
			tempMap.insert(std::make_pair(1 << i), strVal);		// 1 << i means 1 x 2的i次方
		}
	}

	for(auto iVec : tempVec) {
		cout << iVec << " ";
	}
	cout << endl;

	for(auto iMap : tempMap) {
		cout << iMap.first << " " << iMap.second << endl;
	}

	return 0;
}
