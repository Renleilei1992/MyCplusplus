/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：172_go_through_vector.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年08月20日
*   描    述：
*   版    本: Version 1.00
================================================================*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	std::vector<int> vec_01 = {1, 2, 3};

	cout << "------------" << endl;
	// 配合auto进行区间遍历
	for (auto iVec : vec_01) {
		cout << iVec << endl;
	}

	cout << "------------" << endl;
	// 引用区间遍历可以进行数据更改，避免拷贝
	for (int& i : vec_01) {
		i++;
	}

	cout << "------------" << endl;
	// 拷贝式遍历,其实同auto那个
	for (int i : vec_01) {
		cout << i << endl;
	}

	cout << "------------" << endl;
	// 迭代器遍历
	std::vector<int>::iterator it = vec_01.begin();
	for (it; it != vec_01.end(); ++it) {
		cout << *it << endl;
	}

	cout << "------------" << endl;
	// 配合for_each 和 std::begin() std::end()
	for_each(std::begin(vec_01), std::end(vec_01), [](int p){ cout << p << " "; });
	cout << endl;

	return 0;
}
