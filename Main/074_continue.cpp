/*================================================================
*   Copyright (C) 2018 Renleilei. All rights reserved.
*   
*   文件名称：074_continue.cpp
*   创 建 者：Renleilei (renleilei@foxmail.com)
*   创建日期：2018年09月11日
*   描    述：
*   版    本: Version 1.00
================================================================*/

#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
	for(auto i = 0; i < 10; ++i){
		cout << i << endl;
		if(i%2 != 0) {
			continue;
		}
		cout << i << endl;
	}



	return 0;
}
