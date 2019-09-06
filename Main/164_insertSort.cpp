/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：164_insertSort.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年08月14日
*   描    述：插入排序简单测试
*   版    本: Version 1.00
================================================================*/

#include <iostream>

using namespace std;

void insertSort(int arr[], int n);
void printArray(int arr[], int n);

int main()
{
	int arr[5] = {5, 9, 8, 6, 4};
	insertSort(arr, 5);

	printArray(arr, 5);
	return 0;
}

void insertSort(int arr[], int n)
{
	int i, j, base;
	for (i = 1; i < n; i++) {
		base = arr[i];
		j = i - 1;
		while(j >= 0 && arr[j] > base){
			arr[j+1] = arr[j];
			j--;
		}

		arr[j+1] = base;
	}
}

void printArray(int arr[], int n)
{
//	int nCount = sizeof(arr)/sizeof(int);
	for (int i = 0; i < n; i++) {
		std::cout << arr[i] << " ";
	}

	std::cout << std::endl;
}
