/*================================================================
*   Copyright (C) 2018 Renleilei. All rights reserved.
*   
*   文件名称：033_ManyParamter.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2018年03月08日
*   描    述：
*   版    本: Version 1.00
*   编译命令: 
================================================================*/

#include <iostream>

using namespace std;

#define MAX_COUNT 1000
#define MIN_COUNT 10

void func_01(int a1, int a2 = MAX_COUNT, int a3 = 100, int a4 = 10);

int main()
{
	func_01(10);
	func_01(10,10000);
	int A0 = 777;
  int A1 = ++A0;
  func_01(A1, A1, A1);
  cout<<"A0 = "<<A0<<endl;

	bool _b = true;
  int B = _b ? MAX_COUNT :  MIN_COUNT;
  cout<<"B = "<<B<<endl;

	return 0;
}

void func_01(int a1, int a2, int a3, int a4)
{
	cout<<"a1 = "<<a1<<endl;
	cout<<"a2 = "<<a2<<endl;
	cout<<"a3 = "<<a3<<endl;
	cout<<"a4 = "<<a4<<endl;
}
