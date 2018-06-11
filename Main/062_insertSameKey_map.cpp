/*================================================================
*   Copyright (C) 2018 Renleilei. All rights reserved.
*   
*   文件名称：047_insertSameKey_map.cpp
*   创 建 者：Renleilei (renleilei@foxmail.com)
*   创建日期：2018年06月11日
*   描    述：
*   版    本: Version 1.00
*   编译方法: g++ -o main 047_insertSameKey_map.cpp -std=c++11
================================================================*/

#include <iostream>
#include <map>
#include <string>

using namespace std;

int main(int argc, char **argv)
{
	map<int, string> map01;
	map01.insert(std::make_pair(1, "hello"));
	map01.insert(std::make_pair(2, "world"));
	map01.insert(std::make_pair(1, "Hello"));

	// 区间遍历的方式
	for(auto &val_map01 : map01){
		cout << val_map01.first << " " << val_map01.second << endl;
	}

	return 0;
}
