/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：127_bubbleSort.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年05月07日
*   描    述：冒泡排序的实现
*   版    本: Version 1.00
================================================================*/

#include <iostream>

using namespace std;

// 参数: 数组, 数组长度
void bubbleSort(int arr[], int n)
{
	int i, j, tmp;
	for(i = n - 1; i > 0; i--) {
		for(j = 0; j< i; j ++) {
			if(arr[j] > arr[j+1]) {
				tmp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = tmp;
			}
		}
	}
}

int main()
{
	int array[5] = {2, 5, 3, 1, 4};
	bubbleSort(array, sizeof(array)/sizeof(array[0]));

	cout << "冒泡排序结束: ";
	for(int i = 0; i < sizeof(array)/sizeof(array[0]); ++i) {
		cout << array[i] << " ";
	}
	cout << endl;

	return 0;
}
