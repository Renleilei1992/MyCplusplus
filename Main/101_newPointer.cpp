/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：101_newPointer.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年04月18日
*   描    述：
*   版    本: Version 1.00
================================================================*/

#include <iostream>

using namespace std;


class A
{
public:
	A(){
		cout << "A's construction func be called!" << endl;
	}
	~A(){
		cout << "A's destruction func be called!" << endl;
	}
};

class B
{
public:
	B(){
		cout << "B's construction func be called!" << endl;
	}
	~B(){
		cout << "B's destruction func be called!" << endl;
	}
};

void func()
{
	A *a1 = new A();
	B b1 = B();
	
	if(a1 != NULL){
		delete a1;
		a1 = NULL;
	}
}

int main()
{
	cout << "begin..." << endl;
	func();
	cout << "end..." << endl;
	return 0;	
}
