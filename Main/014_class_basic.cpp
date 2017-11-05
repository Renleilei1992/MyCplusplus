/*================================================================
*   Copyright (C) 2017 Renleilei. All rights reserved.
*   
*   文件名称：014_class_RAM.cpp
*   创 建 者：Renleilei (renleilei@foxmail.com)
*   创建日期：2017年11月05日
*   描    述：熟悉类的内存分配
*   版    本: Version 1.00
================================================================*/

#include <iostream>

using namespace std;

class A
{
private:
	int n;
public:
	A(int m):n(m)
	{
	}
	~A(){
	}
};

class B
{
public:
	int a;
	int b;
	char c;
	char* d;
};

int main()
{
	A a(1);				//栈中分配
	A b = A(1); 		//栈中分配
	a = 2;				// 未使用explicit关键词，此处会隐式调用 a = A(2);
	A *c = new A(1);	//堆中分配
	delete c;
	return 0;
}

/*
第一种和第二种没有区别，一是隐式调用，二是显式调用，两种都是在进程虚拟地址空间中的栈中分配内存
第三种使用了new在堆中分配了内存，而栈中内存的分配和释放是由系统管理，堆中内存的分配和释放必须由程序员手动释放

基本数据类型的对象没有析构函数，所以回收基本类型组成的数组空间用delete和delete[]均可
对于类对象数组，只能用delete[]
对于new的单个对象，只能用delte不能用deletep[]
*/
