/*================================================================
*   Copyright (C) 2018 Renleilei. All rights reserved.
*   
*   文件名称：075_auto_test.cpp
*   创 建 者：Renleilei (renleilei@foxmail.com)
*   创建日期：2018年09月18日
*   描    述：
*   版    本: Version 1.00
================================================================*/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void myPrint(int i);

int main()
{
	std::vector<int> vec_01;
	vec_01.push_back(1);
	vec_01.push_back(2);
	vec_01.push_back(3);
	vec_01.push_back(4);

	// use normal iterator
	cout << "With iterator: " << endl;
	std::vector<int>::iterator it = vec_01.begin();
	for(it; it != vec_01.end(); ++it){ cout << *it << endl; }

	// use auto key word
	cout << "With normal auto iterator: " << endl;
	for(auto ivec_01 = vec_01.begin(); ivec_01 != vec_01.end(); ++ivec_01){ cout << *ivec_01 <<endl; }

	// use auto key word with range
	cout << "With auto range: " << endl;
	std::vector<int> vec_02;
	vec_02.swap(vec_01);
	vec_01.clear();
	for(auto  ivec : vec_01){ cout << ivec << endl; }

	// use for_each key word
	cout << "With Normal for_each: " << endl;
	for_each(vec_02.begin(), vec_02.end(), myPrint);

	// use lambda and for_each
	cout << "With Lambda express: " << endl;
	for_each(vec_02.begin(), vec_02.end(), [](int i){ cout << i << endl;});

	// use vector rbegin()
	cout << "With reverse iterator: " << endl;
	std::vector<int>::reverse_iterator iVec_03;
	for(iVec_03 = vec_01.rbegin(); iVec_03 != vec_01.rend(); ++iVec_03){ cout << *iVec_03 << endl; }
	return 0;
}

void myPrint(int i)
{
	cout << i << endl;
}
