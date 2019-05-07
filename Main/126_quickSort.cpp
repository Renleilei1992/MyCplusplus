/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：126_quickSort.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年05月07日
*   描    述：看到MIT的算法导论公开课关于快速排序的讲解之后尝试自己写快排
*   版    本: Version 1.00
*   公开  课: http://open.163.com/movie/2010/12/S/4/M6UTT5U0I_M6V2T7IS4.html
================================================================*/
#include <iostream>

using namespace std;

void quickSort(int arr[], int start, int end);
int partition(int arr[], int start, int end);

int main()
{
	int arr[8] = {6, 10, 13, 5, 8, 3, 2, 11};
	//partition(arr, 0, sizeof(arr)/sizeof(arr[0]) - 1);

	quickSort(arr, 0, sizeof(arr)/sizeof(arr[0]) - 1);

	// print result
	for(int k = 0; k < sizeof(arr)/sizeof(arr[0]); k++) {
		cout << arr[k] << " ";
	}
	cout << endl;
	return 0;
}


void quickSort(int arr[], int start, int end)
{
	cout << "quickSort(): start: " << start << " end: " << end << endl;
	if (start < end) {
		int index = partition(arr, start, end);
		quickSort(arr, start, index - 1);
		quickSort(arr, index + 1, end);
	}
}

// 快速排序算法基础版
// 6  10 13 5  8  3  2  11
// i  j
// 6  5  13 10 8  3  2  11
//    i        j
// 6  5  3  10 8  13 2  11
//       i           j   
// 6  5  3  2  8  13 10 11
//          i           j->(loop end)
// 2  5  3  6  8  13 10 11
//          ^
// 此时6作为主元被交换到i所在的位置(第一次划分使用了6作为划分数组的主元)
// 接下来就将6的下标 r 返回,并初始化两个排序 quickSort(arr, p, r-1) 和 quickSort(arr, r+1, q)
// 初始调用 quickSort(arr, 1, n)
int partition(int arr[], int start, int end)
{
	cout << "partition(): start: " << start << " end: " << end << endl;
	// print array begin 
	cout << "partition() begin: ";
	for(int k = start; k <= end; k++) {
		cout << arr[k] << " ";
	}
	cout << endl;

	int pos = start - 1;
	int base = arr[start];
	int tmp = 0;

	for(int i = start; i <= end; i++) {
		cout << "base: [" << base << "] ";
		if(arr[i] <= base) {
			pos++;
			tmp = arr[pos];
			arr[pos] = arr[i];
			arr[i] = tmp;
		}

		for(int k = start; k <= end; k++) {
  	        cout << arr[k] << " ";
   	    }
        cout << endl;
	}

	tmp = arr[pos];
	arr[pos] = arr[start];
	arr[start] = tmp;

	// print result
	cout << "partition() complete: ";
	for(int k = start; k <= end; k++) {
		cout << arr[k] << " ";
	}
	cout << endl;

	return pos;
}
