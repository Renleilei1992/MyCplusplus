/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：140_binary.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年06月28日
*   描    述：
*   版    本: Version 1.00
================================================================*/

// 需求上下文: 使用32位数字当作勋章信息的返回值，比如返回 200 代表二进制 11001000

#include <iostream>
#include <cmath>
#include <stack>

using namespace std;

int main()
{
	//int A = 2147483647;
	int A = 200;
	for (int i = 0; i < 32; ++i) {
		cout << "----> i: " << i;
		cout << " --> result: " << (A>>i & 1) << endl;
		int temp = (A >> i & 1);
		if (temp == 0) {
			cout << "拥有勋章1: " << pow(2, i) << "号" << endl;
			cout << "拥有勋章2: " << (1 << i) << "号" << endl;
		}
	}

	stack<int> nStack;
	for (int j = 0; j < 32; ++j) {
		//cout << (A >> j & 1);
		int temp = (A >> j & 1);
		nStack.push(temp);
	}

	while(!nStack.empty()) {
		cout << nStack.top();
		nStack.pop();
	}
	cout << endl;

	cout << "0 & 0 : " << (0 & 0) << endl;
	cout << "0 & 1 : " << (0 & 1) << endl;
	cout << "1 & 1 : " << (1 & 1) << endl;

	return 0;
}
