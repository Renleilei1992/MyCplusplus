/*================================================================
*   Copyright (C) 2018 Renleilei. All rights reserved.
*   
*   文件名称：035_SameTypePointer.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2018年03月14日
*   描    述：
*   版    本: Version 1.00
*   编译命令: 
================================================================*/

#include <iostream>

using namespace std;

int main()
{
	const char * ch1 = "hello world";
  char * ch2 = NULL;

  cout<<"ch1's address: "<<&ch1<<endl;
	cout<<"ch1: "<<ch1<<endl;
  cout<<"ch2's address: "<<&ch2<<endl;
//	cout<<"ch2: "<<ch2<<endl;		//空指针无法被访问，内存溢出

//  ch2 = &ch1;
//  cout<<"ch2's address: "<<&ch2<<endl;
//  cout<<"ch2: "<<ch2<<endl;
  
  char *ch3;
  cout<<"ch3's address: "<<&ch3<<endl;
  *ch2 = *ch3;
//  cout<<"ch2's address: "<<&ch2<<endl;
  cout<<"ch2: "<<ch2<<endl;

	return 0;
}
