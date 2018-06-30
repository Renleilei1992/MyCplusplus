/*================================================================
*   Copyright (C) 2018 Renleilei. All rights reserved.
*   
*   文件名称：064_char_length.cpp
*   创 建 者：Renleilei (renleilei@foxmail.com)
*   创建日期：2018年06月16日
*   描    述：
*   版    本: Version 1.00
================================================================*/

#include <iostream>
#include <cstring>

using namespace std;

int main(int argc,char** argv)
{
	char* ch_01 = "hello world!";
	char* ch_02 = "";

	cout << strlen(ch_01) << endl;

	cout << strlen(ch_02) << endl;

	if (ch_02 && ch_02 != "\0")
	{
		cout << "ch_02 is exist!  ->" << ch_02 << endl;
	}
	
	string str_02 = ch_02;
	cout << str_02 << endl;
	
	if (str_02.length() < 1)
	{
		cout << "str_02 is empty!" << endl;
	}

	return 0;
}
