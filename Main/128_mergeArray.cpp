/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：128_mergeArray.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年05月08日
*   描    述：
*   版    本: Version 1.00
================================================================*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void deleteRepeatNum(int arr[], int len);
void mergeArr(int arr1[], int len1, int arr2[], int len2);

int main()
{
	int arr1[5] = {1, 2, 3, 4, 5};
	int arr2[5] = {4, 5, 6, 7, 8};

	mergeArr(arr1, sizeof(arr1)/sizeof(arr1[0]), arr2, sizeof(arr2)/sizeof(arr2[0]));

	return 0;
}

void mergeArr(int arr1[], int len1, int arr2[], int len2)
{
	int index1 = 0;
	int index2 = 0;
	int index3 = 0;
	int arr3[len1 + len2];
	fill(arr3, arr3 + len1 + len2, 0);

	while(index1 < len1 && index2 < len2) {
		arr3[index3++] = arr1[index1] < arr2[index2] ? arr1[index1++] : arr2[index2++];
	}

	if(index1 < len1) {
		for(int j = index1; j < len1; j++) {
			arr3[index3++] = arr1[index1++];
		}
	}
	if(index2 < len2) {
		for(int j = index2; j < len2; j++) {
			arr3[index3++] = arr2[index2++];
		}
	}

	cout << "merge 两有序数组结束: ";
	for(int i = 0; i < len1 + len2; ++i) {
		cout << arr3[i] << " ";
	}
	cout << endl;

	deleteRepeatNum(arr3, len1 + len2);
}

// 删除数组中的重复数据(可借助标准库容器set来去重)
void deleteRepeatNum(int arr[], int len)
{
	vector<int> vec;
	for(int i = 0; i < len; i++) {
		if (find(vec.begin(), vec.end(), arr[i]) == vec.end()) {
			vec.push_back(arr[i]);
		}
	}

	cout << "去重完毕: ";
	for(auto iVec : vec) { cout << iVec << " "; }
	cout << endl;
}

