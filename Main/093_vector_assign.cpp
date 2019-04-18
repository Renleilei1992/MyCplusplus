/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：093_vector_assign.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年03月05日
*   描    述：
*   版    本: Version 1.00
*   编译方法: g++ -o main 093_vector_assign.cpp -std=c++11
================================================================*/

#include <vector>
#include <iostream>
#include <math.h>
#include <algorithm>
//#include <functional>

using namespace std;

int main()
{
	cout<<"program begin..."<<endl;

	const double pi = 4.0 * atan(1.0);
	cout<<"pi = "<<pi<<endl;

	vector<int> _vec_01 = {10, 11, 12, 13, 14, 15, 16};

	vector<int>::const_iterator iter;
	for(iter = _vec_01.begin(); iter != _vec_01.end(); ++iter){
		cout<<*iter<<endl;
	}

	vector<int> _vec_02;
	_vec_02.assign(_vec_01.begin(), _vec_01.end());		// 能正确复制该vector的内容
	for_each(_vec_02.begin(), _vec_02.end(), [ &](int _i){ _i = _i + 1; cout << _i << ","; });
	cout << endl;
	for_each(_vec_02.begin(), _vec_02.end(), [ &](int _i){ cout << _i << ","; });
	cout << endl;

	vector<int> _vec_03;
	_vec_03.assign(7, 10);		// 构造了 7个 10
	for(auto iter = _vec_03.begin(); iter != _vec_03.end(); iter++){
		cout << *iter << " ";
	}
	cout << endl;

	return 0;
}

