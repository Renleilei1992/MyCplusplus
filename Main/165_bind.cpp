/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：165_bind.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年08月14日
*   描    述：
*   版    本: Version 1.00
*	参考文献: https://blog.csdn.net/qq_37653144/article/details/79285221
================================================================*/

#include <iostream>
#include <functional>

using namespace std;

void print(int i, int j) {
	cout << i << " " << i << endl;
}

int main()
{
	using namespace std::placeholders;
	auto func = std::bind([](int i, int j){ cout << i << " " << j << endl; }, 1, 2);
	auto func1 = std::bind([](int i, int j){ cout << i << " " << j << endl; }, _1, _2);

	func();
	func1(99, 188);
	return 0;
}
