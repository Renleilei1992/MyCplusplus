/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：086_std_advance.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年01月04日
*   描    述：
*   版    本: Version 1.00
================================================================*/

#include <iostream>
#include <list>

using namespace std;

int main()
{
	int val_01 = 2;
    std::list<int> list_01;
    list_01.push_back(1);
    list_01.push_back(2);
    list_01.push_back(3);
    list_01.push_back(4);
    list_01.push_back(5);
    list_01.push_back(6);
    list_01.push_back(7);
    list_01.push_back(8);
    list_01.push_back(9);

	std::list<int>::iterator it = list_01.begin();
	std::advance(it, 3);

	cout << "element: " << *it << endl;

	return 0;
}
