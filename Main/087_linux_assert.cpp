/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：087_linux_assert.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年01月11日
*   描    述：
*   版    本: Version 1.00
================================================================*/

#include <iostream>
#include <assert.h>

using namespace std;

int main(int argc, char** argv)
{
	for(int i = 0; i < 20; i++) {
		cout << "---> i = [" << i << "]" << endl;
		if (i == 12) {
			assert("it's 12!!");
		}
	}

	return 0;
}
