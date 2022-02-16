/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：127_bubbleSort.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年05月07日
*   描    述：冒泡排序的实现(时间复杂度O(n^2), 空间复杂度O(1))
*   版    本: Version 1.00
================================================================*/

// 理解时间复杂度和空间复杂度
// 时间复杂度: 个人理解为循环的次数
// 空间复杂度: 个人理解为使用临时变量或者占用空间的大小变化度
// 比如冒泡排序中仅使用了一个中间变量temp,那么它的空间复杂度是O(1)常数级别;

#include <iostream>

using namespace std;

// 参数: 数组, 数组长度	-此方法循环次数少 等差数列求和次循环
void bubbleSort_01(int arr[], int length)
{
	int loopCount = 0;
	int i, j, tmp;
	for(i = length - 1; i > 0; i--) {
		for(j = 0; j < i; j++) {
			if(arr[j] > arr[j+1]) {
				tmp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = tmp;
			}

			loopCount++;
		}
	}

	std::cout << __func__ << "loopCount is " << loopCount << std::endl;
}

// - 此方法循环次数多 n*n
void bubbleSort_02(int arr[], int length)
{
	int loopCount = 0;
	int i, j, temp;
	for(i = 0; i < length; i++) {
		for(j = 0; j < length; j++) {
			if (arr[i] > arr[j]) {
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}

			loopCount++;
		}
	}

	std::cout << __func__ << "loopCount is " << loopCount << std::endl;
}

// 和方法1很类似，循环次数相同
void bubbleSort_03(int arr[], int length)
{
	int loopCount = 0;
	int i, j, temp;
	for (int i = 0; i < length - 1; i++)
	{
		for (int j = 0; j < length - 1 - i; j++)
		{
			if (arr[j] > arr[j + 1]) {
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}

			loopCount++;
		}
	}

	std::cout << __func__ << "loopCount is " << loopCount << std::endl;
}

int main()
{
	int array1[5] = {2, 5, 3, 1, 4};
	bubbleSort_01(array1, sizeof(array1)/sizeof(array1[0]));
	cout << "冒泡排序1结束: ";
	for(int i = 0; i < sizeof(array1)/sizeof(array1[0]); ++i) {
		cout << array1[i] << " ";
	}
	cout << endl;

	int array2[5] = {2, 5, 3, 1, 4};
	bubbleSort_02(array2, sizeof(array2)/sizeof(array2[0]));
	cout << "冒泡排序2结束: ";
	for(int i = 0; i < sizeof(array2)/sizeof(array2[0]); ++i) {
		cout << array2[i] << " ";
	}
	cout << endl;

	int array3[5] = {2, 5, 3, 1, 4};
	bubbleSort_03(array3, sizeof(array3)/sizeof(array3[0]));
	cout << "冒泡排序3结束: ";
	for(int i = 0; i < sizeof(array3)/sizeof(array3[0]); ++i) {
		cout << array3[i] << " ";
	}
	cout << endl;

	return 0;
}
