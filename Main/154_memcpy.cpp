/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：154_memcpy.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年08月07日
*   描    述：
*   版    本: Version 1.00
================================================================*/

#include <string.h>
#include <iostream>

using namespace std;

int main()
{

	char num[10] = {0};
	const char *src = "hello world!!";

	memcpy(num, src, 15);

	cout << "ret: " << num << endl;


	char* src1 = {0};
	const char* dest = "hello";
	if(strcmp(src, dest) == 0) {
		cout << "==0" << endl;
	}
	// malloc
	return 0;
}

