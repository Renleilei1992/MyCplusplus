/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：088_std_list.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年01月16日
*   描    述：
*   版    本: Version 1.00
================================================================*/

#include <iostream>
#include <list>

using namespace std;

int main()
{
	std::list<int> myList;
	for( int i=1; i<10; ++i ){ myList.push_back(i); }

	myList.push_back(11);
	myList.push_back(10);

	for( auto iList : myList ){ cout << iList << endl; } 
	

	return 0;
}
