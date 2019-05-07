/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：121_static.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年05月07日
*   描    述：测试static修饰的局部变量构造和析构的时间
*   版    本: Version 1.00
================================================================*/

#include <iostream>

using namespace std;

class A
{
public:
	A() { cout << "A's construction..\n"; }
	~A() { cout << "A's destruction..\n"; }
};

void print()
{
	static A a;
	cout << "print end.." << endl;
}

int main()
{
	print();

	return 0;
}
