/*================================================================
*   Copyright (C) 2018 Renleilei. All rights reserved.
*   
*   文件名称：030_auto.cpp
*   创 建 者：Renleilei (renleilei@foxmail.com)
*   创建日期：2018年02月02日
*   描    述：
*   版    本: Version 1.00
*	编译方法: g++ -o main 030_auto.cpp -std=c++11 -g -Wall -O3
================================================================*/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void myPrint(int i);

int main()
{
	std::vector<int> vec_01;
	vec_01.push_back(7);
	vec_01.push_back(8);
	vec_01.push_back(9);
	vec_01.push_back(10);

	// use normal iterator
	cout << "With iterator: " << endl;
	std::vector<int>::iterator it = vec_01.begin();
	for(it; it != vec_01.end(); ++it){ cout << *it << endl; }

	// use auto key word
	cout << "With normal auto iterator: " << endl;
	for(auto ivec_01 = vec_01.begin(); ivec_01 != vec_01.end(); ++ivec_01){ cout << *ivec_01 <<endl; }

	// use auto key word with range
	cout << "With auto range: " << endl;
	for(auto  ivec : vec_01){ cout << ivec << endl; }

	// use for_each key word
	cout << "With Normal for_each: " << endl;
	for_each(vec_01.begin(), vec_01.end(), myPrint);

	// use lambda and for_each
	cout << "With Lambda express: " << endl;
	for_each(vec_01.begin(), vec_01.end(), [](int i){ cout << i << endl;});
	return 0;
}

void myPrint(int i)
{
	cout << i << endl;
}
