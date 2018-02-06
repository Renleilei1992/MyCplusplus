/*================================================================
*   Copyright (C) 2018 Renleilei. All rights reserved.
*   
*   文件名称：031_list_reverse.cpp
*   创 建 者：Renleilei (renleilei@foxmail.com)
*   创建日期：2018年02月02日
*   描    述：
*   版    本: Version 1.00
*	编译方法: g++ -o main 031_list_reverse.cpp -g -Wall -O3 -std=c++11
================================================================*/

// reverse the list
#include <iostream>
#include <list>



int main()
{
	std::list<int> myList;
	for( int i=1; i<10; ++i ){ myList.push_back(i); }
	
	// 直接调用了STL中的reverse算法
	myList.reverse();

	std::cout<< "myList contains:" << std::endl;;
	for(auto iList : myList){ std::cout << iList << std::endl; }

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
