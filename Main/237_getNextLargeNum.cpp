/*================================================================
*   Copyright (C) 2020 Renleilei. All rights reserved.
*   
*   文件名称：237_getNextLargeNum.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2020年06月20日
*   描    述：给定数字比如 98675, 找出使用这几个数字组合成的比原有数字大的第一个数字 98765
*   版    本: Version 1.00
================================================================*/

#include <iostream>
#include <vector>

using namespace std;

int count = 0;

int getNextLargeNum(int value);

// 交换数组中两个位置的元素
void swap(std::vector<int>& nums, int source, int dest);

// 构造一个数字
int constructNum(std::vector<int>& nums);

int main()
{
	int originNum = 0;
	std::cout << "plz input originNum: ";
	cin >> originNum;
	int result = getNextLargeNum(originNum);
	std::cout << "next large num is: " << result << std::endl;
	return 0;
}

int getNextLargeNum(int value)
{
	int originNum = value;
	std::vector<int> vec_num;
	while (value > 0) {
		vec_num.emplace_back(value%10);
		value /= 10;
	}

	for (auto iVec : vec_num) {
		std::cout << iVec << " ";
	}
	std::cout << endl;

	// vector中存有这些数字, 并且带顺序
	int nextBigNum = 0;
	int idxLast = 0;
	while (nextBigNum <= originNum) {

		for (int i = 1; i < vec_num.size(); i++) {
			std::vector<int> vec_temp = vec_num;
			swap(vec_temp, idxLast, i);
			nextBigNum = constructNum(vec_temp);
			if (nextBigNum > originNum) {
				break;
			}
		}
		
		if (idxLast < vec_num.size()) {
			idxLast++;
		} else {
			nextBigNum = -1;
			break;
		}
	}

	



	//constructNum(vec_num);

	return nextBigNum;
}

void swap(std::vector<int>& nums, int source, int dest)
{
	if (source < nums.size() && dest < nums.size()) {
		int temp = nums[dest];
		nums[dest] = nums[source];
		nums[source] = temp;
	}
}

int constructNum(std::vector<int>& nums)
{
	int result = 0;
	int param = 1;
	for (int i = 0; i < nums.size(); ++i) {
		result += nums[i] * param;
		param *= 10;
	}

	count++;
	cout << __func__ << ": " << result << " times: " << count << endl;
	return result;
}
