/*================================================================
*   Copyright (C) 2018 Renleilei. All rights reserved.
*   
*   文件名称：081_autoVec.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2018年12月05日
*   描    述：
*   版    本: Version 1.00
================================================================*/

#include <iostream>
#include <vector>

using namespace std;

struct FansInfo
{
	int x = 1;
	int y = 2;
	int z = 3;
};

typedef std::vector<FansInfo> InviteVec;

int main(int argc, char** argv)
{
	FansInfo fansInfo;
	fansInfo.x = 10;
	fansInfo.y = 20;

	std::vector<FansInfo> vec_01;

	vec_01.push_back(fansInfo);

	for (auto iVal : vec_01) {
		cout << iVal.x << " " << iVal.y << " " << iVal.z << endl;
	}

	InviteVec vec_02;
	vec_02.push_back(fansInfo);

	for (auto iVal1 : vec_02) {
		cout << iVal1.x << " " << iVal1.y << " " << iVal1.z << endl;
	}
		
	return 0;
}
