/*================================================================
*   Copyright (C) 2018 Renleilei. All rights reserved.
*   
*   文件名称：070_unordered_map.cpp
*   创 建 者：Renleilei (renleilei@foxmail.com)
*   创建日期：2018年07月31日
*   描    述：
*   版    本: Version 1.00
*	编译指令: g++ -o main 070_unordered_map.cpp -std=c++11
================================================================*/


// 一个奇怪的现象,当此文件在 Ubuntu Linux系统中编译后的执行结果符合期望:
// map: 			Hello world
// unordered_map: 	Horldw olle
// 当同样的文件在MacOS系统中编译后的执行结果不符合期望,均为 Hello world
// 暂时不明真相


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
