/*================================================================
*   Copyright (C) 2017 Renleilei. All rights reserved.
*   
*   文件名称：013_iterator.cpp
*   创 建 者：Renleilei (renleilei@foxmail.com)
*   创建日期：2017年11月05日
*   描    述：熟悉iterator用法与实现c++11的新特性及lamanda表达式
*   版    本: Version 1.00
*   编译方法: g++ -std=c++11 -o main 013_iterator.cpp -O3 -g -Wall
================================================================*/

#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;

void printElem(int& elem);
void printElem_1(int elem, const char* prefix);

int main()
{
	/* vector的第一种初始化方法 */
	int ia[] = {1, 2, 3};
	cout<<"sizeof(ia)/sizeof(int) = ["<<sizeof(ia)/sizeof(int)<<"]"<<endl;
	vector<int> ivec(ia, ia + sizeof(ia)/sizeof(int));
	
	/* vector的第二种初始化方法 */
	vector<int> _vec02 = {10, 11, 12, 13, 14, 15, 16};

	/* 1.使用迭代器遍历容器 */
	for(vector<int>::const_iterator iter = ivec.begin(); iter != ivec.end(); ++iter){
		cout<< *iter << endl;
	}
	/* 2.使用for_each遍历容器 */
	for_each(ivec.begin(), ivec.end(), printElem);
	for_each(ivec.begin(), ivec.end(), bind2nd(ptr_fun(printElem_1), "Element: "));
	/* 3.for_each 与 lamanda 表达式的结合遍历容器使代码简洁 */
	for_each(ivec.begin(), ivec.end(), [ &](int _A){ _A = _A + 1; cout<<_A<<","<<endl;});		//output: 2, 3, 4
	/* 4.for loop auto 区间遍历 */
	for(auto iter = _vec02.begin(); iter != _vec02.end(); iter++){		//基础型迭代器与auto遍历
		cout<< (*iter) <<endl;
	}
	for(auto val : _vec02){
		cout<< val <<endl;
	}
}

// for_each() 事实上是一个function template, 实现如下
/******

template<typename InputIterator, typename Function>
Function for_each(InputIterator beg, InputIterator end, Fucntion f){
	while(beg != end)
		f(*beg++);
}

*******/

void printElem(int& elem){
	cout<< elem <<endl;
}

void printElem_1(int elem, const char* prefix){
	cout<< prefix << elem <<endl;
}
