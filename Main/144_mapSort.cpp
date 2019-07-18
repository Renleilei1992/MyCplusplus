/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：144_mapSort.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年07月03日
*   描    述：
*   版    本: Version 1.00
*	编译指令: g++ -o main 144_mapSort.cpp -std=c++11
================================================================*/

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{

	// -------------- vector sort --------------------
	std::vector<int> vec_01 = {1, 4, 5, 2, 3};	// c++11
	for	(auto iVec : vec_01) {
		cout << iVec << " ";
	}
	cout << endl;

//	std::sort(vec_01.begin(), vec_01.end(), [](int a, int b){ return (a < b); });	// 升序 // 匿名函数不需要使用外界的变量,此处用空、=、&均可正常运行
	std::sort(vec_01.begin(), vec_01.end(), [](int a, int b){ return (a > b); });	// 降序	// 匿名函数不需要使用外界的变量,此处用空、=、&均可正常运行
	for	(auto iVec : vec_01) {
		cout << iVec << " ";
	}
	cout << endl;
	// -------------- vector sort --------------------


	// -------------- map    sort --------------------
	std::map<int, int> map_01;
	map_01.insert(std::make_pair(5, 200));
	map_01.insert(std::make_pair(3, 500));
	map_01.insert(std::make_pair(1, 300));
	map_01.insert(std::make_pair(4, 100));
	map_01.insert(std::make_pair(2, 400));
	cout << "key: ";
	for (auto iMap : map_01) {
		cout << iMap.first << " ";
	}
	cout << endl;
	cout << "val: ";
	for (auto iMap : map_01) {
		cout << iMap.second << " ";
	}
	cout << endl;

	// map 不能直接使用sort函数进行排序, 此处将map中的pair转存如vector;
	std::vector<pair<int, int>> vec_02;
	for (auto iMap : map_01) {
		vec_02.push_back(std::make_pair(iMap.first, iMap.second));
	}
	cout << "vec<pair>.key: ";
	for (auto iVec : vec_02) {
		cout << iVec.first << " ";
	}
	cout << endl;

	cout << "vec<pair>.val: ";
	for (auto iVec : vec_02) {
		cout << iVec.second << " ";
	}
	cout << endl;
	
	cout << "-----------> sort begin: " << endl;
	std::sort(vec_02.begin(), vec_02.end(), [](std::pair<int, int> a, std::pair<int, int> b){ return (a.second > b.second); });
	cout << "vec<pair>.key: ";
	for (auto iVec : vec_02) {
		cout << iVec.first << " ";
	}
	cout << endl;

	cout << "vec<pair>.val: ";
	for (auto iVec : vec_02) {
		cout << iVec.second << " ";
	}
	cout << endl;

	return 0;
}
