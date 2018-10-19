/*================================================================
*   Copyright (C) 2018 Renleilei. All rights reserved.
*   
*   文件名称：076_explicit.cpp
*   创 建 者：Renleilei (renleilei@foxmail.com)
*   创建日期：2018年10月19日
*   描    述：
*   版    本: Version 1.00
================================================================*/

#include <iostream>

using namespace std;

class A
{
public:
	A(int i = 10){
		m_i = i;
	}

public:
	int m_i = 1;
};

class B
{
public:
	explicit B(int i = 100){
		m_i = i;
	}
public:
	int m_i = 1;
};

int main(int argc, char **argv)
{
	int x = 99;
	
	A a;
	a = x;			//隐式转换成功
	//a = A(x);		//这样构造是没问题的,不管有没有explicit关键字,都能构造成功

	cout << "=====> a.m_i = " << a.m_i << endl;

	B b;
	//b = x;		//隐式转换会报错
	b = B(x);

	cout << "=====> b.m_i = " << b.m_i << endl;

	return 0;
}
