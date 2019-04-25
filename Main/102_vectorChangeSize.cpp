/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：102_vectorChangeSize.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年04月24日
*   描    述：
*   版    本: Version 1.00
================================================================*/

#include<iostream>
#include<vector>
using namespace std;

void mycapacity(const vector<int>& vec)
{
    cout << "分配总空间大小为：" << vec.capacity() << endl;
}

void mysize(const vector<int>& vec)
{
    cout << "已用空间大小为：" << vec.size() << endl;
}

void myprint(const vector<int>& vec)
{
    for (int i = 0; i < vec.size(); ++i)
        cout << vec[i] << ",";
    cout << endl;
}


int main()
{
    vector<int> vec;
    cout << "起始状态：" << endl;
    mycapacity(vec);
    mysize(vec);
    cout << "========================" << endl;

    for (int i = 0; i < 10; ++i) {
        vec.push_back(i);
        cout << "压入第" << i+1 << "个元素之后：" << endl;
        myprint(vec);
        mycapacity(vec);
        mysize(vec);
        cout << "========================" << endl;
    }

	// 如果在编写程序的时候能够预测到大多数情况vector的size范围,可以先使用 reserve() 进行空间分配的操作，以避免多次内存扩充
	cout << "---------- 第二次验证 -------------" << endl;
	vector<int> vec_01;
	vec_01.reserve(16);	// 预先分配16的内存空间
	for (int j = 0; j < 17; ++j) {
		vec_01.push_back(j);
        cout << "压入第" << j+1 << "个元素之后：" << endl;
        myprint(vec_01);
        mycapacity(vec_01);
        mysize(vec_01);
        cout << "========================" << endl;
	}

    return 0;
}
