/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：095_pointer_addr2.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年03月07日
*   描    述：
*   版    本: Version 1.00
================================================================*/

#include <iostream>
#include <string.h>

using namespace std;

struct st1
{
	int x = 0;
	int y = 1;
};

int main()
{
	int a = 10000;
	int b = 22222;
	int c = 33333;

	int *p1 = &a;
	int *p2 = &b;
	int *p3 = &c;

	cout << "p1的值为(指针即地址，指针的值即是一个地址): " << p1 << endl;		// 0x7ffc5a3bb1b0 (这是一个内存地址)
	cout << "p1指向的内存地址的内容为 *p1: " << *p1 << endl;					// 10000, 这个地址里存储的内容为 10000;
	cout << "存放p1这个指针的地址 &p1: " << &p1 << endl;						// 0x7fffc92df848 (这个内存地址是存放 p1值(地址)的地方)
	cout << "p1这个指针" << *(&p1) << endl;										// 0x7ffc5a3bb1b0 (这个操作相当于 p1)

	int *p4 = (int *)p1;
	cout << "p4的值为: " << p4 << endl;								// 0x7ffc5a3bb1b0 (这是一个内存地址)
	cout << "p4指向的内存地址的内容为 *p4:" << *p4 << endl;			// 10000, 这个地址里存储的内容为 10000;
	cout << "p4这个指针的地址 &p4: " << &p4 << endl;

	memcpy(p4, p2, sizeof(int));
	cout << "p4的值为: " << p4 << endl;								// 0x7ffc5a3bb1b0 (这是一个内存地址)
	cout << "p4指向的内存地址的内容为 *p4: " << *p4 << endl;		// 22222, 这个地址里存储的内容为 22222;
	cout << "p4这个指针的地址 &p4: " << &p4 << endl;

	memcpy((void *)p4, (void *)p3, sizeof(int));
	cout << "p4的值为: " << p4 << endl;								// 0x7ffc5a3bb1b0 (这是一个内存地址)
	cout << "p4指向的内存地址的内容为 *p4: " << *p4 << endl;		// 33333, 这个地址里存储的内容为 33333;
	cout << "p4这个指针的地址 &p4: " << &p4 << endl;

	char *c1 = new char[1024];
	char *c2 = c1;
	memset(c2, 0, 1024);
	cout << "c1的内存地址为: &c1: " << &c1 << endl;
	cout << "c2的值为: c2: " << c2 << endl;
	cout << "c2的内存地址为: &c2: " << &c2 << endl;
	c2 = "hello pointer";
	cout << "------------" << endl;
	cout << "c1的值为: c1: " << c1 << endl;
	cout << "c1的内存地址为: &c1: " << &c1 << endl;
	cout << "c2的值为: c2: " << c2 << endl;
	cout << "c2的内存地址为: &c2: " << &c2 << endl;
	cout << "------------" << endl;
//	char *c3 = "hello world!";
	char *c3 = (char *)c2;
	c3 = "hello world!";
//	memcpy(c2 + 20, c3, (strlen(c3)));
	cout << "c1的值为: c1: " << c1 << endl;
	cout << "c1的内存地址为: &c1: " << &c1 << endl;
	cout << "c2的值为: c2: " << c2 << endl;
	cout << "c2的内存地址为: &c2: " << &c2 << endl;
	cout << "c3的值为: c3: " << c3 << endl;
	cout << "c3的内存地址为: &c3: " << &c3 << endl;


	return 0;
}
