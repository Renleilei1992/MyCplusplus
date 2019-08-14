/*================================================================
*   Copyright (C) 2018 Renleilei. All rights reserved.
*   
*   文件名称：046_sizeofChar.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2018年04月25日
*   描    述：
*   版    本: Version 1.00
*   编译命令: 
================================================================*/

#include <iostream>
#include <cstring>

using namespace std;

int main()
{
	const char * ch01 = "hello world!  nihao???";

	cout<<"size: "<<sizeof(ch01)<<endl;
	cout<<"string len: "<<strlen(ch01)<<endl;

	std::string str01(ch01);

	cout<<"length: "<<str01.length()<<endl;

	char str[0];
	cout << "size: " << sizeof(str) << endl;
	cout << "size: " << sizeof(&str) << endl;

	char str1[1];
	cout << "size: " << sizeof(str1) << endl;
	return 0;
}
