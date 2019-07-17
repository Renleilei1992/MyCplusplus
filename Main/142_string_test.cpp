/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：142_string_test.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年07月01日
*   描    述：
*   版    本: Version 1.00
================================================================*/

#include <iostream>
#include <cstring>

using namespace std;

int main()
{
	std::string strArray[3] = {"", "", ""};
	std::string str = "";

	for(int i = 0; i < 5; ++i) {
		str = "hello_" + to_string(i);		// to_string() 方法可以将数字转换为字符串
		if(i < 3 && !str.empty()) {
			strArray[i] = str;
		}
	}

	for(int j = 0; j < 3; ++j) {
		cout << strArray[j] << endl;
	}

	return 0;
}
