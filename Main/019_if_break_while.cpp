/*================================================================
*   Copyright (C) 2017 Renleilei. All rights reserved.
*   
*   文件名称：019_if_break_while.cpp
*   创 建 者：Renleilei (renleilei@foxmail.com)
*   创建日期：2017年11月19日
*   描    述：
*   版    本: Version 1.00
*   编译方法: g++ -o main 019_if_break_while.cpp -O3 -g -Wall
================================================================*/


#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

extern "C"

int main()
{
	int count = 0;

	while(count < 5){
		printf("count = [%d]\n", count);
		if(count%2 == 0){
			count++;
		//	break;
			continue;
		}
		count++;
	}

	return EXIT_SUCCESS;
}
