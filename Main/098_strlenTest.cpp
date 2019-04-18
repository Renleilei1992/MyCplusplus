/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：098_strlenTest.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年03月25日
*   描    述：
*   版    本: Version 1.00
================================================================*/

#include <iostream>
#include <string.h>
#include <stdlib.h>


using namespace std;

int main()
{
	char *c1 = "hello";

	cout << "stlen(c1): " << strlen(c1) << endl;	

	c1 = NULL;
//	cout << "stlen(c1): " << strlen(c1) << endl;	

	char * c2 = NULL;

	free(c2);
	delete c2;

	return 0;
}
