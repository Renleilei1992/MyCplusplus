/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：135_autoVector.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年05月21日
*   描    述：注意vector等STL容器的使用,遍历过程中安全erase迭代器避免迭代器失效
*   版    本: Version 1.00
*	编译指令: g++ -o main 135_autoVector.cpp -std=c++11
================================================================*/

#include <vector>
#include <iostream>

using namespace std;

int main()
{
	vector<int> _vec_01 = {10, 11, 12, 13, 14, 15, 16};

	for(auto iVec : _vec_01) {
		cout << "---- split -----";
		cout << iVec << endl;
		_vec_01.pop_back();
		for(auto iVec1 : _vec_01) {
			cout << iVec1 << endl;
		}
	}

	// 迭代器失效的问题见如下解决办法
	cout << "----- 迭代器失效场景 -----" << endl;
	vector<int> _vec_02 = {10, 11, 12, 13, 14, 15, 16};
	for (auto iVec : _vec_02) {
		cout << iVec << " " << endl;
		if(iVec == 13) {
			//_vec_02.erase(iVec);
			cout << "loop find it" << endl;
		}
	}

	// 安全一点的迭代器使用 erase
	for (vector<int>::iterator iter = _vec_02.begin(); iter != _vec_02.end();) {
		cout << *iter << " " << endl;
		if(*iter == 13) {
			cout << "loop find it" << endl;
			iter = _vec_02.erase(iter);
		} else {
			iter++;
		}

	}

	return 0;
}
