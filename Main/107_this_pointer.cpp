/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：107_this_pointer.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年04月26日
*   描    述：
*   版    本: Version 1.00
================================================================*/

#include <iostream>
#include <cstdio>

using namespace std;

class A {
public:
	A(){
		cout << "A's construction func be called, this pointer's addr: " << this << endl;
		printf("this's addr: %p - 0x%x \n", this, this);
	}
	~A(){
		cout << "A's deconstruction func be called, this pointer's addr: " << this << endl;
		printf("this's addr: %p - 0x%x \n", this, this);
	}

};


int main()
{
	A *_a = new A();
	cout << "_a's addr: " << _a << endl;
	if (_a != NULL) {
		delete _a;
		_a = NULL;
	}


	A a;
	cout << "a's addr: " << &a << endl;	

	return 0;
}
