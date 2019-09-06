/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：173_to_through_map.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年08月20日
*   描    述：
*   版    本: Version 1.00
================================================================*/

#include <iostream>
#include <map>
#include <cstring>

using namespace std;

int main()
{
	std::map<int, string> map_01;
	map_01.insert(make_pair<int, string>(1, "hello world1!!"));
	map_01.insert(make_pair<int, string>(2, "hello world2!!"));
	map_01.insert(make_pair<int, string>(3, "hello world3!!"));

	for (auto iMap : map_01) {
		cout << iMap.first << " " << iMap.second << endl;
	}


	cout << "---------" << endl;
	for (pair<int, string> iPair : map_01) {
		cout << iPair.first << " " << iPair.second << endl;
	}
	return 0;
}
