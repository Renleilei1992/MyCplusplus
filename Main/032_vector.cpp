/*================================================================
*   Copyright (C) 2018 Renleilei. All rights reserved.
*   
*   文件名称：032_vector.cpp
*   创 建 者：Renleilei (renleilei@foxmail.com)
*   创建日期：2018年02月27日
*   描    述：
*   版    本: Version 1.00
*   编译命令: 
================================================================*/

#include <vector>
#include <iostream>
#include <math.h>

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

	return 0;
}

