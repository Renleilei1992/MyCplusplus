/*================================================================
*   Copyright (C) 2018 Renleilei. All rights reserved.
*   
*   文件名称：044_vector_pointer.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2018年04月19日
*   描    述：
*   版    本: Version 1.00
*   编译命令: 
================================================================*/

#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

struct p1
{
	p1()
		: beginnum(0)
		, endnum(0)
	{}
	int beginnum;
	int endnum;
};

int main()
{
	cout<<"program begin..."<<endl;

	const double pi = 4.0 * atan(1.0);
	cout<<"pi = "<<pi<<endl;

	//vector<int> _vec_01 = {10, 11, 12, 13, 14, 15, 16};

	vector<int> _vec_01;
	int num = 0;
	_vec_01.push_back(num);
	num = 1;
	_vec_01.push_back(num);

	vector<int>::const_iterator iter;
	for(iter = _vec_01.begin(); iter != _vec_01.end(); ++iter){
		cout<<*iter<<endl;
	}

	vector<p1> _vec_02;
	p1 p001;
	p001.beginnum = 1;
	p001.endnum = 2;
	_vec_02.push_back(p001);
	p001.beginnum = 3;
	p001.endnum = 4;
	_vec_02.push_back(p001);

	//vector<p1>::const_iterator iter_01;
	//for(iter_01 = _vec_02.begin(); iter_01 != _vec_02.end(); ++iter_01){
	//	cout<<&iter_01.beginnum<<" "<<&iter_01.endnum<<endl;
	//}

	for(int i = 0; i < _vec_02.size(); ++i)
	{
		cout<<_vec_02[i].beginnum<<" "<<_vec_02[i].endnum<<endl;
	}

	return 0;
}

