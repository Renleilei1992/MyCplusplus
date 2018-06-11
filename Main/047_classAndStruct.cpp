/*================================================================
*   Copyright (C) 2018 Renleilei. All rights reserved.
*   
*   文件名称：047_classAndStruct.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2018年04月28日
*   描    述：
*   版    本: Version 1.00
*   编译命令: g++ -o main 047_classAndStruct.cpp -g -Wall -O3
================================================================*/

#include <iostream>

using namespace std;

class A
{
	struct B
	{
		void B_print();

		int uBnum;
	};

	void A_print();

	int uAnum;
};

int main()
{

	A a;
	a.A_print();

	return 0;
}

void B_print()
{
	cout<<"i'm B_print"<<endl;
}

void A::A_print()
{
	cout<<"i'm A_print"<<endl;
}

