/*================================================================
*   Copyright (C) 2018 Renleilei. All rights reserved.
*   
*   文件名称：040_QuestionMark.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2018年04月11日
*   描    述：
*   版    本: Version 1.00
*   编译命令: 
================================================================*/

#include <iostream>

using namespace std;

int main(int argc, char **argv)
{

	int retCode = 1;
	int retCode01 = 0;

	int val_01 = retCode ? 1 : 0;
	int val_02 = retCode01 ? 1 : 0;

	cout<<"val_01 = "<<val_01<<endl;
	cout<<"val_02 = "<<val_02<<endl;

	return 0;
}
