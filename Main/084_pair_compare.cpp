/*================================================================
*   Copyright (C) 2018 Renleilei. All rights reserved.
*   
*   文件名称：084_pair_compare.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2018年12月27日
*   描    述：
*   版    本: Version 1.00
================================================================*/

#include <iostream>
#include <utility>

using namespace std;

int main()
{
	pair<int, int> p1(2, 2);
	pair<int, int> p2(2, 2);

	if (p1 == p2) {
		cout << "p1 == p2" << endl;
	} else {
		cout << "p1 != p2" << endl;
	}

	return 0;
}
