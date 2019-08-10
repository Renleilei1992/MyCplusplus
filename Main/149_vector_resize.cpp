/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：149_vector_resize.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年07月29日
*   描    述：
*   版    本: Version 1.00
================================================================*/

#include <vector>
#include <iostream>

using namespace std;

struct test {
	int m_uid = 0;
	bool m_bVal = false;
};

int main()
{
	std::vector<int> vec;
//	vec.resize(0);
//	vec.resize(1);


	vector<int> vec_01 = {10, 11, 12, 13, 14, 15, 16};
	for(auto ivec : vec_01) { cout << ivec << endl; }

	vector<test> vec_02;
	test t1, t2;
	t1.m_uid = 1;
	t2.m_uid = 2;
	t2.m_bVal = true;

	vec_02.push_back(t1);
	vec_02.push_back(t2);

	for(auto ivec : vec_02) {
		cout << ivec.m_uid << " " << ivec.m_bVal << endl;
	}

	for(auto &ivec : vec_02) {
//		cout << ivec->m_uid << " " << ivec->m_bVal << endl;
	}

	return 0;
}
