/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：221_binarySearch.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年12月05日
*   描    述：二分查找简单使用
*   版    本: Version 1.00
================================================================*/

#include <iostream>
#include <algorithm>

using namespace std;

// 以下方法处理的是不重复的有序数组
int binarySearch_1(int arr[], int len, int target);						// 普通版二分查找
int binarySearch_Recur(int arr[], int target, int low, int high);		// 递归版二分查找


int main()
{
	int arr_1[7] = {1, 2, 3, 3, 4, 4, 5};
	int target_1 = 8;
	cout << "arr_1 数组中查找元素[" << target_1 << "] 下标为: " << binarySearch_1(arr_1, 7, target_1) << endl;
	cout << "arr_1 数组中查找元素[" << target_1 << "] 下标为: " << binarySearch_Recur(arr_1, target_1, 0, 7) << endl;
	return 0;
}

int binarySearch_1(int arr[], int len, int target)
{
	cout << __func__ << endl;
	int low = 0, high = len - 1;
	while(low <= high) {
		int mid = low + (high - low) / 2;
		if (arr[mid] < target) { low = mid + 1; }
		if (arr[mid] > target) { high = mid - 1; }
		if (arr[mid] == target) { return mid; }
	}

	return low;
}

int binarySearch_Recur(int arr[], int target, int low, int high)
{
	cout << __func__ << endl;
	
	if (low > high) { return low; }
	
	int mid = low + (high - low) / 2;
	if (arr[mid] > target) {
		return binarySearch_Recur(arr, target, low, mid - 1);
	} else if (arr[mid] < target) {
		return binarySearch_Recur(arr, target, mid + 1, high);
	}

	return mid;
}
