/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：163_vector_delete.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年08月13日
*   描    述：
*   版    本: Version 1.00
================================================================*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void removeAtIndex(vector<int>& vec, int idx);

int main()
{
	std::vector<int> vec = {0, 1, 2, 3, 4, 5, 6};

	for (auto iVec : vec) { cout << iVec << endl; }

	removeAtIndex(vec, 3);

	cout << "----- remove end! ------" << endl;
	for (auto iVec : vec) { cout << iVec << endl; }

	std::sort(vec.begin(), vec.end(), [](int a, int b){
		return a < b;
	});

	cout << "----- sort end! ------" << endl;
	for (auto iVec : vec) { cout << iVec << endl; }

	return 0;
}

void removeAtIndex(vector<int>& vec, int idx)
{
	if (idx < vec.size()) {
		vec[idx] = vec.back();
	}

	vec.pop_back();
}
