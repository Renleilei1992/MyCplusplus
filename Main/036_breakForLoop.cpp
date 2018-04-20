/*================================================================
*   Copyright (C) 2018 Renleilei. All rights reserved.
*   
*   文件名称：036_breakForLoop.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2018年03月15日
*   描    述：
*   版    本: Version 1.00
*   编译命令: 
================================================================*/

#include <iostream>

using namespace std;

int main()
{
	for(int i = 0; i < 10; ++i)
	{
		cout<<"i = "<<i<<endl;
		if(i > 5)
		{
//			break;
			continue;
		}
	}
	std::string str;
	cout<<str<<"cout end!"<<endl;

	return 0;
}
