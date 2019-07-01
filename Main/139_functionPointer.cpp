/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：139_functionPointer.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年06月05日
*   描    述：
*   版    本: Version 1.00
================================================================*/

#include <iostream>
#include <unistd.h>

using namespace std;

class A
{
public:
	A(){ cout << "A's construction be called!" << endl; }
	~A(){ cout << "A's destruction be called!" << endl; }
	
	void print() { cout << "A's print() be called!" << endl; }
};

void testFunc(A a) { 
	cout << "testFunc(A a): ";
	a.print();
}

void testFunc1(A &a) {
	sleep(1);
	cout << "testFunc1(A &a): ";
	a.print();
}

void testFunc2(A *a) {
	
	sleep(1);

	if (a == nullptr) {
		cout << "testFunc2(A *a): a is nullptr" << endl;
	}

	cout << "testFunc2(A *a): ";
	a->print();
}

void func01() {
	cout << "-----------> func01() be called!" << endl;
	A *a = new A();
	testFunc2(a);

	delete a;
	a = nullptr;
}


void func02() {
	cout << "-----------> func02() be called!" << endl;
	A *a = new A();
	testFunc1(*a);

	delete a;
	a = nullptr;
}



int main()
{

	A a1;
	A *b1 = &a1;
	A *c1 = new A();

	testFunc(a1);
	testFunc1(a1);
	testFunc2(c1);

	delete c1;
	c1 = nullptr;

	func01();
	func02();
	return 0;
}
