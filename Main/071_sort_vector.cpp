/*================================================================
*   Copyright (C) 2018 Renleilei. All rights reserved.
*   
*   文件名称：071_sort_vector.cpp
*   创 建 者：Renleilei (renleilei@foxmail.com)
*   创建日期：2018年07月31日
*   描    述：
*   版    本: Version 1.00
================================================================*/

#include <iostream>
#include <vector>
#include<algorithm>

using namespace std;

class A
{
public:
	A(int _a, int _b)
	{
		a = _a;
		b = _b;
	};

	int a;
	int b;
};


int main()
{
	std::vector<A> _vec_A;
	for(int i = 0; i < 10; ++i){
		A a(i, 10 - i);
		_vec_A.push_back(a);
	}

//	for(auto ivec : _vec_A){ cout << ivec << endl;}

//	sort(_vec_A.begin(), _vec_A.end(), [](A a1, A a2){
//		return a1.a > a2.a;
//	});
	
//	for(auto ivec : _vec_A){ cout << ivec << endl;}

	return 0;
}
