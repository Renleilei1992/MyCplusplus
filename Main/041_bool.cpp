/*================================================================
*   Copyright (C) 2018 Renleilei. All rights reserved.
*   
*   文件名称：040_bool.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2018年04月16日
*   描    述：
*   版    本: Version 1.00
*   编译命令: 
================================================================*/

#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
	bool bShow_01 = (1 ? true : false) || (0 ? true : false);

	cout<<"bShow_01 = "<<bShow_01<<endl;

	return 0;
}
