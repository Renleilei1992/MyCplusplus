/*================================================================
*   Copyright (C) 2018 Renleilei. All rights reserved.
*   
*   文件名称：063_map_auto.cpp
*   创 建 者：Renleilei (renleilei@foxmail.com)
*   创建日期：2018年06月12日
*   描    述：
*   版    本: Version 1.00
================================================================*/

#include <iostream>
#include <map>

using namespace std;

int main(int argc, char **argv)
{
	std::map<int, std::string> map_01;
	map_01.insert(std::make_pair(1, "hello"));
	map_01.insert(std::make_pair(2, "world"));
	map_01.insert(std::make_pair(3, "!!!!"));

	for (auto iter = map_01.begin(); iter != map_01.end(); ++iter){
		cout << iter->second <<endl;
		if (iter->first == 2){
			cout << "2 -> jump out from the loop!!!" <<endl;
			break;
		}
	}

	return 0;
}
