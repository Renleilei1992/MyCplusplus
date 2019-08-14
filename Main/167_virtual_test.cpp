/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：167_virtual_test.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年08月15日
*   描    述：
*   版    本: Version 1.00
================================================================*/

#include <iostream>

using namespace std;

class B
{
public:
	B() { cout << __func__ << endl; }
	virtual ~B() { cout << __func__ << endl; }

	virtual void print() { cout << __func__ << " B: " << endl; }
};

class D1 : public B
{
public:
	D1() { cout << __func__ << endl; }
	virtual ~D1() { cout << __func__ << endl; }

	virtual void print() { cout << __func__ << " D1: " << endl; }
};


class D2 : public B
{
public:
	D2() { cout << __func__ << endl; }
	virtual ~D2() { cout << __func__ << endl; }

	virtual void print() { cout << __func__ << " D2: " << endl; }
};


int main()
{
	D1 d1;
	D2 d2;

	B* b1 = &d1;
	B* b2 = &d2;

	b1->print();
	b1 = nullptr;
	b2 = nullptr;
	cout << "program end!!" << endl;
	return 0;
}
