/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：119_pack_problem.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年05月06日
*   描    述：
*   版    本: Version 1.00
================================================================*/
#include <iostream>
#include <algorithm>
using namespace std;

int *w = NULL;		// 存储每件物品重量的数组指针
int *v = NULL;		// 存储每件物品价值的数组指针
int **T = NULL;		// 存储背包问题表格的数组指针
int n;				// 物品个数n
int W;				// 背包总承重W

// 返回两个值的最大值
int max(int a, int b)
{
	return (a > b) ? a : b;
}

// 迭代法，能显示背包问题的表格
void packIterative()
{
	// 循环遍历n行
	for (int i = 1; i <= n; ++i)
	{
		// 循环遍历W列
		for (int j = 1; j <= W; ++j)
		{
			//第i个物品能装下，则比较包括第i个物品和不包括第i个物品，取其最大值
			if (w[i] <= j)
				T[i][j] = max(v[i] + T[i - 1][j - w[i]], T[i - 1][j]);

			// 第i个物品不能装下，则递归装i-1个
			else
				T[i][j] = T[i - 1][j];
		}
	}
}

// 递归法，不支持显示背包问题的表格
int packRecursive(int i, int j, int *w, int *v)
{
	// 结束条件（初始条件），i或者j为0时最大总价值为0
	if (i == 0 || j == 0)
		return 0;

	// 第i个物品不能装下，则递归装i-1个
	if (w[i] > j)
		return packRecursive(i - 1, j, w, v);

	//第i个物品能装下，则比较包括第i个物品和不包括第i个物品，取其最大值
	else
		return max(v[i] + packRecursive(i - 1, j - w[i], w, v), packRecursive(i - 1, j, w, v));
}

// 打印背包问题的表格
void printT(int n, int W)
{
	// 打印n行
	for (auto i = 0; i <= n; i++)
	{
		// 打印行数
		cout << i << ":\t";

		// 打印W列
		for (int w = 0; w <= W; w++)
		{
			cout << T[i][w] << "\t";
		}

		// 换行
		cout << endl;
	}
}

int main()
{

	cout << "---------------- 背包问题 ----------------" << endl;
	cout << "请输入物品数 n (n>=0) " << endl;

	// 输入背包数
	cin >> n;

	if (cin.fail() || n < 0)
	{
		cout << "输入n错误！" << endl;
//		system("pause");
		return 0;
	}

	cout << "请输入背包承重量 W (W>=0) " << endl;

	// 输入背包承重量
	cin >> W;

	if (cin.fail() || W < 0)
	{
		cout << "输入W错误！" << endl;
//		system("pause");
		return 0;
	}

	// 分配空间
	// 对w和v分配n+1大小
	w = new int[n+1];
	v = new int[n+1];

	// 对T分配n+1行，并初始化为0
	T = new int *[n + 1]();
	// 对T分配W+1列，并初始化为0
	for (auto i = 0; i <= n; i++)
	{
		T[i] = new int[W + 1]();
	}

	// 输入背包的重量和价值
	for (auto i = 1; i <= n; i++)
	{
		cout << "请输入第 " << i << " 个背包的重量和价值（用空格隔开）" << endl;
		cin >> w[i] >> v[i];
		if (cin.fail() || w[i] < 0 || v[i] < 0)
		{
			cout << "输入错误！" << endl;
//			system("pause");
			return 0;
		}
	}

	cout << "------------------------------------------------" << endl;
	cout << "请选择算法：" << endl;
	cout << "【1】迭代法" << endl;
	cout << "【2】递归法" << endl;
	cout << "------------------------------------------------" << endl;

	int choose;

	// 输入算法的选择
	cin >> choose;
	switch (choose)
	{
	case 1:
	{
		// 迭代法，能显示背包问题的表格
		packIterative();
		cout << "能装下物品的最大价值为 " << T[n][W] << endl;
		cout << "------------------------------------------------" << endl;
		printT(n, W);
		break;
	}
	case 2:
	{
		// 递归法，不支持显示背包问题的表格
		cout << "能装下物品的最大价值为 " << packRecursive(n, W, w, v) << endl;
		break;
	}
	default:
	{
		cout << "输入错误！" << endl;
		break;
	}
	}

	cout << "------------------------------------------------" << endl;

//	system("pause");
	return 0;
}
