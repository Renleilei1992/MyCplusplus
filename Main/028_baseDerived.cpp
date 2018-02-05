/*================================================================
*   Copyright (C) 2018 Renleilei. All rights reserved.
*   
*   文件名称：028_baseDerived.cpp
*   创 建 者：Renleilei (renleilei@foxmail.com)
*   创建日期：2018年01月30日
*   描    述：
*   版    本: Version 1.00
================================================================*/

#include <iostream>

using namespace std;

class Base
{
public:
	Base(){cout<<"Base Construct ..."<<endl;};
	~Base(){cout<<"Base Deconstruct ..."<<endl;}
public:
	int a;	
};

class Derived : public Base
{
public:
	Derived(int i):b(i){cout<<"Derived Construct..."<<endl;}
	~Derived(){cout<<"Derived Deconstruct ..."<<endl;}
public:
	int b;
};



int main()
{
	Base *b = new Derived(1);
	cout<<"b->a = "<<b->a<<endl;
//	cout<<"b->b = "<<b->b<<endl;

	delete b;

	return 0;
}
