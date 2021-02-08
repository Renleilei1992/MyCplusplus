/*================================================================
*   Copyright (C) 2020 Renleilei. All rights reserved.
*   
*   文件名称：226_test_new.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2020年01月16日
*   描    述：
*   版    本: Version 1.00
================================================================*/

#include <iostream>

using namespace std;

class A
{
public:
	A() { cout << __func__ << "::A()" << endl; }
	~A() { cout << __func__ << "::~A()" << endl; }
};

void testA();

int main()
{
	cout << "----test begin---" << endl;
	testA();
	cout << "----test end---" << endl;
	
	return 0;
}

void testA()
{
	A* a1 = new A();
	A a2;
}
