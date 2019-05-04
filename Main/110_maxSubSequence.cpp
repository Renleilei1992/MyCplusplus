/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：110_maxSub_01Sequence.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年04月30日
*   描    述：求最大子序列和、绝对值最大子序列以及其区间
*   版    本: Version 1.00
================================================================*/

// 任一数字序列 {-5, 4, -20, 16, -2, -3}, 最大子序列和: 16, 区间: [3, 3](数组下标从0开始);

#include <iostream>

using namespace std;

// 最大子序列和
int maxSub_01(const int a[], int n);	// 此方法的时间复杂度为 O(n^2)
int maxSub_02(const int a[], int n);	// 此方法的时间复杂度为 O(n)

int main(int argc, char** argv)
{
	int array[10] = {-1, -2, 5, -6, 20, -10, 1, 9, -5};

	for(int i = 0; i < sizeof(array)/sizeof(int); ++i) { cout << " " << array[i]; }
	cout << " 数组长度: " << sizeof(array)/sizeof(int) << endl;
	cout << "最大子序列和的值为: " << maxSub_01(array, sizeof(array)/sizeof(int)) << endl;
	cout << "最大子序列和的值为: " << maxSub_02(array, sizeof(array)/sizeof(int)) << endl;


	return 0;
}


int maxSub_01(const int a[], int n)
{
	int max, sum, begin, end, i, j;
	max = sum = begin = end = 0;
	for (i = 0; i < n; ++i) {
		sum = 0;	// 置0 临时sum
		for(j = i; j < n; ++j) {
			sum += a[j];	// 计算区间和
			if (sum > max) {
				max = sum;
				begin = i;
				end = j;
			}
		}
	}

	cout << "方法01-最大子序列区间为: [" << begin << ", " << end << "]" << endl;

	return max;
}

int maxSub_02(const int a[], int n)
{
	int curSum = 0;
	int maxSum = 0;
	int begin = 0;
	int end = 0;

	for (int i = 0; i < n; ++i) {
		curSum += a[i];

		if (curSum > maxSum) {
			maxSum = curSum;
			end = i;
		}

		// 此处判断为最大子序列区间的开始下标不明白为啥?????
		if (curSum < 0) {
			curSum = 0;
			begin = i + 1 >= n ? i : i + 1;
		}
	}

	cout << "方法02-最大子序列区间为: [" << begin << ", " << end << "]" << endl;

	return maxSum;
}
