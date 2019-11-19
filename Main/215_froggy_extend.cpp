/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：215_froggy_extend.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年11月15日
*   描    述：青蛙每次可以跳1级台阶或者2级台阶,问n级台阶共有多少种方式?
*   版    本: Version 1.00
*   编译指令: g++ -o main 215_froggy_extend.cpp -std=c++11
================================================================*/

#include <iostream>
#include <chrono>

using namespace std;

int calPlan_1(int n);	// 迭代法
int calPlan_2(int n);	// 递归法: 当超过40级台阶时,递归会非常耗时
void showTime(bool isRecursion, int n);

int main()
{
	showTime(false, 40);	// Waited: 0.035085 ms
	showTime(true, 40);		// Waited: 792.47 ms
	return 0;
}

void showTime(bool isRecursion, int n)
{
	int ret = 0;
	auto start = std::chrono::high_resolution_clock::now();
	if (isRecursion) {
		ret = calPlan_2(n);
		cout << "recursion method: " << ret << endl;
	} else {
		ret = calPlan_1(n);
		cout << "iteration method: " << ret << endl;
	}
	auto end = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double, std::milli> elapsed = end - start;
	cout << "Waited: " << elapsed.count() << " ms\n";
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

// 递归法
int calPlan_2(int n)
{
	if (n == 0) { return 0; }
	if (n == 1) { return 1; }
	if (n == 2) { return 2; }

	if (n > 2) {
		return calPlan_2(n - 1) + calPlan_2(n - 2);
	}
}
