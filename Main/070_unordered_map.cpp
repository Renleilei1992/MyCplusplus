/*================================================================
*   Copyright (C) 2018 Renleilei. All rights reserved.
*   
*   文件名称：070_unordered_map.cpp
*   创 建 者：Renleilei (renleilei@foxmail.com)
*   创建日期：2018年07月31日
*   描    述：
*   版    本: Version 1.00
================================================================*/

#include <iostream>
#include <map>
#include <unordered_map>

using namespace std;

int main()
{
	std::map<int, char> map_01;

//	typedef std::unordered_map<int, char> map_noSort;
//	map_noSort map_02;
	std::unordered_map<int, char> map_02;
    char ch[11] = {'H','e','l','l','o',' ','w','o','r','l','d'};
    for(int i = 10; i >= 0; --i)
    {
		map_01.insert(std::make_pair(i, ch[i]));
		map_02.insert(std::make_pair(i, ch[i]));
    }

	for (auto iter = map_01.begin(); iter != map_01.end(); ++iter){
        cout << iter->second;
    }
	cout<<endl;

	//for (map_noSort::iterator it = map_02.begin(); it != map_02.end(); ++it){
	for (auto iter = map_02.begin(); iter != map_02.end(); ++iter){
        cout << iter->second;
	}
	cout<<endl;


	return 0;
}
