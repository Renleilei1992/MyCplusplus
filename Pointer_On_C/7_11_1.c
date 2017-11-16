/*================================================================
*   Copyright (C) 2017 Renleilei. All rights reserved.
*   
*   文件名称：7_11_1.c
*   创 建 者：Renleilei (renleilei@foxmail.com)
*   创建日期：2017年11月16日
*   描    述：
*   版    本: Version 1.00
*   编译方法: gcc -o main 7_11_1.c -O3 -g -Wall
================================================================*/


#include <stdio.h>


int hermite(int n, int x);

int main(int argc, char *argv[])
{
	int val_1 = hermite(0, 5);
	int val_2 = hermite(1, 5);
	int val_3 = hermite(3, 5);
	int val_4 = hermite(4, 5);

	printf("val_1 = %d\n", val_1);
	printf("val_2 = %d\n", val_2);
	printf("val_3 = %d\n", val_3);
	printf("val_4 = %d\n", val_4);

	return 0;
}

int hermite(int n, int x)
{
	if(n <= 0)
		return 1;
	if(n == 1)
		return 2*x;

	return 2*x*hermite(n-1, x) - 2*(n-1)*hermite(n-2, x);
}
