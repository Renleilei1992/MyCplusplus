/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：166_print_all.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年08月14日
*   描    述：
*   版    本: Version 1.00
================================================================*/

#include <iostream>
#include <cstdio>

#define MAX_NUM 100

using namespace std;

void swap(int &a, int &b);
void printAll(int a, int b, int c);
void printAll_1(int a);
void f(int a[], int n, int k);

int tot = 0;

int main()
{

	cout << "---> print begin!!" <<endl;

	printAll(1, 2, 3);

	cout << "----> another func: " << endl;
	int n = 0;
	int *arr = new int[n];
	for(int i = 0; i < 3; i++) {
		arr[i] = i + 1;
	}

	int arr1[4] = {1, 2, 3, 4};
	f(arr1, 4, 0);
	cout << "共计排列数: " << tot << endl;
	return 0;
}

void swap(int &a, int &b)
{
	int tmp = a;
	a = b;
	b = tmp;
}

void printAll(int a, int b, int c)
{
	printf("%d %d %d\n", a, b, c);
	swap(a, b);	// 交换前两个数字
	printf("%d %d %d\n", a, b, c);
	swap(b, c);	// 交换后两个数字

	// 一个周期结束
	if(a == 1 && b == 2) return;

	printAll(a, b, c);	// 递归
}

void f(int a[], int n, int k)
{
	if(k==n){
		tot ++;
		for(int i=0; i<n; i++){
			cout << a[i] << " ";
		}
		cout << endl;
	}

	for(int i = k; i < n; i++){
		swap(a[k], a[i]);
		f(a, n, k+1);
		swap(a[k], a[i]);
	}
}
