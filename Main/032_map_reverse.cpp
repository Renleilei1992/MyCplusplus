/*================================================================
*   Copyright (C) 2018 Renleilei. All rights reserved.
*   
*   文件名称：032_map_reverse.cpp
*   创 建 者：Renleilei (renleilei@foxmail.com)
*   创建日期：2018年02月02日
*   描    述：
*   版    本: Version 1.00
================================================================*/


// reverse the map
#include <iostream>
#include <map>
#include <string>

int main()
{
	std::map<int, char> myMap;
	char ch[11] = {'H','e','l','l','o',' ','w','o','r','l','d'};
	for(int i = 1; i < 10; ++i)
	{
		myMap(i) = ch[i-1];
	}
	
	// 直接调用了STL中的reverse算法
/*	myMap.reverse();

	std::cout<< "myMap contains:" << std::endl;;
	for(auto iMap : myMap){ std::cout << iMap << std::endl; }
*/
	std::map<int, char>::iterator it = myMap.begin();
	for(it; it != myMap.end(); ++it)
	{
		
	}
	return 0;
}

// 重写reverse算法


// reverse 源码
/*
template<class BidrIt>
void reverse(BidirIt first, BidrIt last)
{
	while((first != last) && (first != --last))
	{
		std::ioter_swap(first++, last);
	}
}
*/
