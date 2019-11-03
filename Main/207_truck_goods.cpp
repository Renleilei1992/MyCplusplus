/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：207_truck_goods.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年10月28日
*   描    述：货车货物问题
*   版    本: Version 1.00
================================================================*/

/*
	背景: 100~300重量范围的一批货物,卡车载重300,最少可以用多少辆卡车装完货物?
*/

#include <iostream>
#include <vector>

using namespace std;

int cal(int arr[], int goodsNum);
void quickSort(int arr[], int start, int end);
int partition(int arr[], int start, int end);

int main()
{
	int goods_arr[10] = {101, 150, 180, 200, 280, 120, 100, 100, 100, 120};	// 10件货物
	quickSort(goods_arr, 0, sizeof(goods_arr)/sizeof(goods_arr[0]) - 1);


	cal(goods_arr, sizeof(goods_arr)/sizeof(goods_arr[0]) - 1);
	return 0;
}

int cal(int arr[], int goodsNum)
{
	for (int i = 0; i <= goodsNum; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;

	int truckNum = 0;
	std::vector<int> vec_1;
	for (int i = goodsNum; i >= 0; i--) {
		if (arr[i] > 200 && arr[i] <= 300) {
			truckNum++;
			continue;
		}

		vec_1.emplace_back(arr[i]);
	}

/*
	cout << "auto vector: ";
	std::vector<int> vec(arr, arr + goodsNum);
	for (auto iVec : vec) {
		cout << iVec << " ";
		
	}
	cout << endl;
*/
	cout << "truckNum: " << truckNum << endl;
	cout << "auto vector: ";
	for (auto iVec : vec_1) {
		cout << iVec << " ";
		
	}
	cout << endl;

	return 0;
}

void quickSort(int arr[], int start, int end)
{
	if (start < end) {
		int index = partition(arr, start, end);
		quickSort(arr, start, index - 1);
		quickSort(arr, index + 1, end);
	}
}

int partition(int arr[], int start, int end)
{
	int pos = start - 1;
	int base = arr[start];
	int tmp = 0;
	for (int i = start; i <= end; i++) {
		if (arr[i] <= base) {
			pos++;
			tmp = arr[pos];
			arr[pos] = arr[i];
			arr[i] = tmp;
		}
	}

	tmp = arr[start];
	arr[start] = arr[pos];
	arr[pos] = tmp;

	return pos;
}

/*
int partition(int arr[], int start, int end) {
	
	int pos = start - 1;
	int base = arr[start];
	int tmp = 0;

	for (int i = start; i <= end; i++) {
		if (arr[i] <= base) {
			pos++;
			tmp = arr[pos];
			arr[pos] = arr[i];
			arr[pos] = tmp;
		}
	}

	tmp = arr[start];
	arr[start] = arr[pos];
	arr[pos] = tmp;

	return pos;
}
*/
