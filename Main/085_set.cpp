/*================================================================
*   Copyright (C) 2018 Renleilei. All rights reserved.
*   
*   文件名称：085_set.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2018年12月27日
*   描    述：
*   版    本: Version 1.00
================================================================*/

#include <iostream>
#include <set>

using namespace std;

int main()
{
	set<int> set_01;
	set_01.insert(1);
	set_01.insert(2);
	set_01.insert(3);
	set_01.insert(4);

	for (auto iSet : set_01) {
		cout << " iSet.value: " << iSet << endl;
	}

	if (set_01.insert(3).second) {
		cout << "insert 3 success!" << endl;
	} else {
		cout << "insert 3 failed!" << endl;
	}

	return 0;
}
