/*================================================================
*   Copyright (C) 2018 Renleilei. All rights reserved.
*   
*   文件名称：080_switch_case.cpp
*   创 建 者：Renleilei (renleilei@foxmail.com)
*   创建日期：2018年11月27日
*   描    述：
*   版    本: Version 1.00
================================================================*/


#include <iostream>

using namespace std;

int main()
{
	int i = 10;
	int j = 0;

	int ret_val = 1;
	switch(true)
	{
		case (i > 3) :
			cout << "======> case 1" << endl;;
			break;
		case (i > 5) :
			cout << "======> case 2" << endl;
			break;
		default:
			cout << "======> no answer!" << endl;
			break;
	}

	cout << "===========> end!" << endl;


	return 0;
}
