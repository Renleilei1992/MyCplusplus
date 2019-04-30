/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：108_bigNum_multiplication.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年04月27日
*   描    述：大数相乘
*   版    本: Version 1.00
*	参考文献: https://blog.csdn.net/u010983881/article/details/77503519
================================================================*/

#include <iostream>

using namespace std;


// 自定义的数组长度计算函数模板
template<class T>
int length(T &arr){
	return sizeof(arr) / sizeof(arr[0]);
}


int getNumLength(long num)
{
	int i = 0;
	while(num != 0){
		i++;
		num /= 10;
	}

	return i;
}


long multiBigNum(long num1, long num2)
{
	// 递归终止条件
	if(num1 < 10 || num2 < 10) return num1 * num2;

	// 计算拆分长度
	int size1 = getNumLength(num1);
	int size2 = getNumLength(num2);
	int halfN = size1 >= size2 ? size1/2 : size2/2;

	// 拆分为 a, b, c, d
	long a;
	
}


int main()
{
	int a = 123;
	int b = 456;

	cout << "a*b = " << a*b << endl;

	int _a[] = {1, 2, 3};
	int _b[] = {4, 5, 6};

	cout << "_a 数组: ";
	for(int i = 0; i < sizeof(_a)/sizeof(int); ++i) {
		cout << _a[i] << " ";
	}
	cout << "长度为: " << length(_a) << endl;

	cout << "_b 数组: ";
	for(int i = 0; i < sizeof(_b)/sizeof(int); ++i) {
		cout << _b[i] << " ";
	}
	cout << "长度为: " << length(_b) << endl;

	return 0;
}
