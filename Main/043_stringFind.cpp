/*================================================================
*   Copyright (C) 2018 Renleilei. All rights reserved.
*   
*   文件名称：043_stringFind.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2018年04月18日
*   描    述：
*   版    本: Version 1.00
*   编译命令: 
================================================================*/

#include <iostream>

using namespace std;

int main()
{
	std::string str01 = "hello world lo!";

	std::string str02 = "lo";

	int num01 = str01.find(str02, 0);
	int num02 = str01.find(str02, num01+1);

	cout<<num01<<endl;
	cout<<num02<<endl;
//	cout<<str01.Mid(num01, num02) << endl;

	std::string str03 = "lo";
	if(str02 == str03)
	{
		cout<<"equal!"<<endl;
	}
	return 0;
}
