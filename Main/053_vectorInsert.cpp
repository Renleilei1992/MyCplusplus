/*================================================================
*   Copyright (C) 2018 Renleilei. All rights reserved.
*   
*   文件名称：053_vectorInsert.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2018年05月28日
*   描    述：
*   版    本: Version 1.00
*   编译命令: g++ -o main 053_vectorInsert.cpp -std=c++11
================================================================*/

#include <iostream>
#include <vector>


using namespace std;

int main(int argc, char** argv)
{
	int val_01 = 2;
	std::vector<int> vec_01;
	vec_01.push_back(1);
	vec_01.push_back(2);
	vec_01.push_back(3);
	vec_01.push_back(4);
	vec_01.push_back(5);

	vector<int>::iterator iter = vec_01.begin();
	vector<int>::iterator mid = vec_01.begin() + vec_01.size()/2;
	
	int count = 0;
	while(iter != mid){
		if(*iter == val_01){
			vec_01.insert(iter, 2*val_01);
			cout<<"success"<<endl;
			break;
		}
		count++;
		iter++;
		cout<<count<<"     *iter="<<*iter<<"    *mid="<<*mid<<endl;

		if(count > 10){
				break;
		}
	}

	for(auto ivec : vec_01){cout << ivec << endl;}

	return 0;
}
