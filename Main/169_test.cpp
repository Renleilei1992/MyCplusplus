/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：169_test.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年08月15日
*   描    述：
*   版    本: Version 1.00
================================================================*/

#include <iostream>

using namespace std;

int main()
{
	int *count = new int(5);
	cout << "cout :" << *count << endl;		// 5
	delete count;
	return 0;
}
