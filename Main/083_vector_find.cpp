/*================================================================
*   Copyright (C) 2018 Renleilei. All rights reserved.
*   
*   文件名称：083_vector_find.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2018年12月26日
*   描    述：
*   版    本: Version 1.00
================================================================*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	int val_01 = 2;
    std::vector<int> vec_01;
    vec_01.push_back(1);
    vec_01.push_back(2);
    vec_01.push_back(3);
    vec_01.push_back(4);
    vec_01.push_back(5);

	if (find(vec_01.begin(), vec_01.end(), 3) != vec_01.end()) {
		cout << " find the element!!" << endl;
	}

	return 0;
}
