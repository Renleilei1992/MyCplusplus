/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：208_for_interview.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年11月02日
*   描    述：
*   版    本: Version 1.00
================================================================*/

#include <iostream>

using namespace std;

void quickSort(int arr[], int begin, int end);
int partition(int arr[], int begin, int end);

class A
{
public:
	virtual void show1() { cout << "show 1" << endl; }
	void show2() { cout << "show 2" << endl; }
};

int main()
{
	int arr[10] = { 8, 9, 4, 6, 2, 7, 5, 1, 0, 3};
	quickSort(arr, 0, 9);

	for (int i = 0; i < 10; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;

	A *ptr_a = nullptr;
	ptr_a->show2();		// will success.
//	ptr_a->show1();		// Segmentation fault
	return 0;
}

void quickSort(int arr[], int begin, int end)
{
	if(begin < end) {
		int idx = partition(arr, begin, end);
		quickSort(arr, begin, idx - 1);
		quickSort(arr, idx + 1, end);
	}
}

int partition(int arr[], int begin, int end)
{
	int pos = begin - 1;
	int base = arr[begin];
	int tmp;
	for (int i = begin; i <= end; i++) {
		if (arr[i] <= base) {
			pos++;
			tmp = arr[i];
			arr[i] = arr[pos];
			arr[pos] = tmp;
		}
	}

	tmp = arr[pos];
	arr[pos] = arr[begin];
	arr[begin] = tmp;

	return pos;
}
