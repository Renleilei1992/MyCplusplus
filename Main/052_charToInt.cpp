/*================================================================
*   Copyright (C) 2018 Renleilei. All rights reserved.
*   
*   文件名称：052_charToInt.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2018年05月14日
*   描    述：
*   版    本: Version 1.00
*   编译命令: 
================================================================*/

#include <iostream>
#include <cstdlib>

using namespace std;

void print_01(const char * str)
{
	cout<< str <<endl;
}

int main()
{
	uint32_t i = 1;
	char c = '0';
	char c1 = c + i;

	cout << c1  << "   "<<sizeof(c1)<<endl;
	//cout << c1  << "   "<<sizeof(c1) << "   "<<typeof(c1).name()<<endl;

	cout<<i<<"   "<<c<<endl;
	const char c2 = c + i;
	const char * c3 = "hello world";
	print_01(&c2);
	print_01(c3);
//	print_01(c3);


	int i1 = 123456;
	char buffer[6] = {0};

//	itoa(i1, buffer, 10);		//Mac端的编译器不支持此函数
	snprintf(buffer, 7, "%d", i1);	// 此函数Mac端支持
	print_01(buffer); 
	cout<<sizeof(buffer)<<endl;
	return 0;
}

