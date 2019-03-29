/*================================================================
*   Copyright (C) 2017 Renleilei. All rights reserved.
*   
*   文件名称：015_class_RAM.cpp
*   创 建 者：Renleilei (renleilei@foxmail.com)
*   创建日期：2017年11月05日
*   描    述：
*   版    本: Version 1.00
*   编译方法: g++ -o main 015_class_RAM.cpp -O3 -g -Wall
================================================================*/

#include <iostream>
#include <cstdlib>

using namespace std;

class A
{
public:
	int a;		//当只有a时, sizeof(A) = 4
	char b;		//当只有b时, sizeof(A) = 1; 当同时存在a,b时, sizeof(A) = 8	内存对齐
	char *c;	//当只有c时, sizeof(A) = 8; 当同时存在a,b,c时, sizeof(A) = 16
	A(int _val1, char _val2, char *_val3):a(_val1),b(_val2),c(_val3){
	}
	void print(int _val1){
		cout<<"A.a: "<<a<<endl;
		cout<<"A.b: "<<b<<endl;
		cout<<"A.c: "<<c<<endl;
		cout<<"_val1: "<<_val1<<endl;
	}
};

class B
{
};

int main()
{
	cout<<sizeof(A)<<endl;		//总结: 成员函数不占内存空间
	cout<<sizeof(B)<<endl;		//总结: 空类占大小为 1
	char ch[10] = "hello!";
	A _Aval(1,'c',ch);
	cout<<"_Aval.a: "<<_Aval.a<<endl;
	cout<<"_Aval.b: "<<_Aval.b<<endl;
	cout<<"_Aval.c: "<<_Aval.c<<endl;
	_Aval.print(89);

	return EXIT_SUCCESS;
}
