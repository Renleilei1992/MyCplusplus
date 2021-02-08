/*================================================================
*   Copyright (C) 2020 Renleilei. All rights reserved.
*   
*   文件名称：230_argc_CommandArguments.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2020年03月19日
*   描    述：测试主入口函数的参数以及参数个数的demo
*   版    本: Version 1.00
================================================================*/

#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	for (int i = 0; i < argc; ++i) {
		cout << __func__ << ":: argc=" << argc << " argc[" << i << "]=" << argv[i] << endl; 
	}
	return 0;
}
