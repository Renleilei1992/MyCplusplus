/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：178_test_tuple.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年08月22日
*   描    述：使用c++11的元组新特性,以替代之前嵌套pair的做法
*   版    本: Version 1.00
================================================================*/

#include <iostream>
#include <tuple>		// std::make_tuple

using namespace std;

int main()
{
	auto t1 = std::make_tuple("str1", "str2", "str3", 4);		// std::tuple<string, string, string, int>
	for (int i = 0; i < 4; ++i) {
//		cout << __func__ << " t1[" << i << "]: " << std::get<i>(t1) << endl;		// get<1>(t1)	需要常量 constant value 
	}

	// 基于下标的访问
	cout << "t1[0]: " << std::get<0>(t1) << endl;
	cout << "t1[1]: " << std::get<1>(t1) << endl;
	cout << "t1[2]: " << std::get<2>(t1) << endl;
	cout << "t1[3]: " << std::get<3>(t1) << endl;

	auto i = std::get<3>(t1);
	decltype(i) j = i;
	cout << "j/2: " << j/2 << endl;
	return 0;
}
