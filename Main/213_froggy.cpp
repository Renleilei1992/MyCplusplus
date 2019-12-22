/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：213_froggy.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年11月15日
*   描    述：青蛙每次可以跳1级台阶或者2级台阶,问n级台阶共有多少种方式?
*   版    本: Version 1.00
================================================================*/

#include <iostream>

using namespace std;

int calPlan_1(int n);	// 迭代法
int calPlan_2(int n);	// 递归法

int main()
{

	int ret = calPlan(4);
	cout << "plans num: " << ret << endl;
	return 0;
}

// 迭代法: 效率非常高
int calPlan_1(int n)
{
	int former1 = 1;
	int former2 = 2;
	int target = 0;

	if (n == 0) { return 0; }
	if (n == 1) { return 0; }
	if (n == 2) {
		return 2;
	} else if ( n > 2) {
		for (int i = 3; i <= n; i++) {
			target = former1 + former2;
			former1 = former2;
			former2 = target;			
		}
	}

	return target;
}

int calPlan_2(int n)
{
	if (n == 0) { return 0; }
	if (n == 1) { return 1; }
	if (n == 2) { return 2; }

	if (n > 2) {
		return calPlan_2(n - 1) + calPlan_2(n - 2);
	}
}
