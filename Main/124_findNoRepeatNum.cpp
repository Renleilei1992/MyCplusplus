/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：124_findNoRepeatNum.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年05月07日
*   描    述：找出数组中不重复的1个数字或者2个数字
*   版    本: Version 1.00
================================================================*/

#include <iostream>

using namespace std;

void find1NoRepeatNum(int a[], int len, int &result);
void find1NoRepeatNum(int a[], int len, int &result);

int main()
{
	int arr[5] = {1,2,1,2,3};
	int arr1[6] = {1,2,5,1,2,3};
	int res = 0;
	int res1 = 0;
	find1NoRepeatNum(arr, sizeof(arr)/sizeof(arr[0]), res);
	find1NoRepeatNum(arr1, sizeof(arr1)/sizeof(arr1[0]), res1);
	cout << "找出数组中不重复的1个数字: " << res << endl;
	cout << "找出数组中不重复的1个数字: " << res1 << endl;
	return 0;
}

// 找出数组中的1个未重复的数字
void find1NoRepeatNum(int a[], int len, int &result)
{
	if(len <= 2) { return; }
	for(int i = 0; i < len; ++i) {
		cout << "---befor ^--- result: " << result << " a[" << i << "]" << a[i] << endl;
		result ^= a[i];
		cout << "---after ^--- result: " << result << " a[" << i << "]" << a[i] << endl;
	}
}
