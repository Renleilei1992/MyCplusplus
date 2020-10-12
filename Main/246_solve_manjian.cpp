/*================================================================
*   Copyright (C) 2020 Renleilei. All rights reserved.
*   
*   文件名称：246_solve_manjian.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2020年10月10日
*   描    述：为了解决满减凑单的问题进行暴力实现
*   版    本: Version 1.00
================================================================*/

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int g_index = 1;
std::map<int, std::vector<int>> g_mapVecs;

// 计算阶乘
int Factorial(int n);
// 计算数列求和
int SumArray(int array[], int len);
int SumVector(std::vector<int>& vec);
// 打印出一个vector的所有元素
void printVec(std::vector<int>& vec);
// 将数组转为字符串，中间用空格隔开
std::string vecConvertToString(const std::vector<int>& vec);
// N个数字选取其中任意的K个数字组合出
void comb(int N, int k, const std::vector<int>& priceVec);
// 计算满减(含交互)
void func();

int main()
{
	std::cout << "Factorial: " << Factorial(10) << std::endl;

	int array[10] = {50, 49, 80, 110, 135, 39, 60, 72, 30, 40};
	std::vector<int> vec = {50, 49, 80, 110, 135, 39, 60, 72, 30, 40};
	std::cout << "SumArray: " << SumArray(array, 10) << std::endl;
	std::cout << "SumVector: " << SumVector(vec) << std::endl;

	printVec(vec);

	//comb(10, 8, vec);

	
	/*
	for (auto iMap : g_mapVecs) {
		std::cout << "map key: " << iMap.first << " map value: ";
		printVec(iMap.second);
	}
	*/

	func();
	return 0;
}

void func()
{
	int singlePriceNums = 0;
	std::cout << "Plz input you have 多少个商品单价: ";
	std::cin >> singlePriceNums;
	std::vector<int> vec = {50, 49, 80, 110, 135, 39, 60, 72, 30, 40};

	// step1: 将所有可能的数组都汇总出来
	for (int i = 1; i <= singlePriceNums; i++) {
		// 将所有可能的数组全部写入到 g_mapVecs
		comb(singlePriceNums, i, vec);
	}
	
	// step2: 将每个数组求和
	/*
	for (auto iMap : g_mapVecs) {
		std::cout << "map key: " << iMap.first << " map value: ";
		printVec(iMap.second);
	}
	*/
	std::map<std::string, int> retMap;
	std::cout << "组合价钱可能为: ";
	for (auto iMap : g_mapVecs) {
		int retSum = SumVector(iMap.second);
		std::cout << " " << retSum;
		std::string vecStr = vecConvertToString(iMap.second);
		retMap.insert(std::make_pair(vecStr, retSum));
	}
	std::cout << endl;

	// 筛选出在预期价位的结果.
	int expectedPrice = 380;
	int priceSection = 30;
	for (auto iMap : retMap) {
		if (iMap.second > 380 && iMap.second <= 410) {
			std::cout << "商品组合为: " << iMap.first << " 该组合价钱: " << iMap.second << std::endl;
		}
	}

}

// 计算阶乘
int Factorial(int n)
{
	if (n <= 1) return 1;

	return n*Factorial(n-1);
}

// 计算数列求和
int SumArray(int array[], int len)
{
	int ret = 0;
	for (int i = 0; i < len; i++) {
		ret += array[i];
	}

	return ret;
}

int SumVector(std::vector<int>& vec)
{
	int ret = 0;
	for (auto iVec : vec) {
		ret += iVec;
	}

	return ret;
}

// 打印出一个vector的所有元素
void printVec(std::vector<int>& vec)
{
	for (auto iVec : vec) {
		std::cout << iVec << " ";
	}

	std::cout << std::endl;
	return;
}

// 计算组合值(m必须大于n, 正整数)
int CalCombination(int m, int n)
{
}

// 将数组转为字符串，中间用空格隔开
std::string vecConvertToString(const std::vector<int>& vec)
{
	std::string retString;
	for (auto iVec : vec) {
		retString += std::to_string(iVec);
		retString += " ";
	}
	return retString;
}

// N个数字选取其中任意的K个数字组合出
void comb(int N, int k, const std::vector<int>& priceVec)
{
	std::string bitmask(k, 1);	// K leading 1's
	std::cout << "bitmask 1: " << bitmask << " size: " << bitmask.size() << std::endl;

	bitmask.resize(N, 0);		// N-K trailing 0's
	std::cout << "bitmask 2: " << bitmask << " size: " << bitmask.size() << std::endl;

	// print
	do {
		std::vector<int> tmpVec;
		for (int i = 0; i < N; ++i) {
			if (bitmask[i]) {
				 std::cout << " " << i;
				 tmpVec.emplace_back(i);
			}
		}
		std::cout << std::endl;

		// tempVec 中暂时只存储了数组中的index值
		for (int j = 0; j < tmpVec.size(); j++) {
			int truePrice = priceVec[tmpVec[j]];
			tmpVec[j] = truePrice;
			//std::cout << " " << truePrice;
		}
		//std::cout << std::endl;

		std::pair<int, std::vector<int>> pair = std::make_pair(g_index, tmpVec);
		g_mapVecs.insert(pair);
		g_index++;
	} while (std::prev_permutation(bitmask.begin(), bitmask.end()));
}
