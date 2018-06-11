/*================================================================
*   Copyright (C) 2018 Renleilei. All rights reserved.
*   
*   文件名称：051_stringEqual.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2018年05月14日
*   描    述：
*   版    本: Version 1.00
*   编译命令: 
================================================================*/

#include <iostream>
#include <string>

using namespace std;

int main(int argc, char **argv)
{
	uint32_t uInt_01 = 10001;
	std::string str_01 = "10000";
	std::string str_02 = std::to_string(uInt_01);

	if(str_01 == str_02){
		cout<<str_01<<" == "<<str_02<<endl;
	}else{
		cout<<str_01<<" != "<<str_02<<endl;
	}	
	
	if(str_01 == "10000"){
		cout<<str_01<<" equal 10000!!"<<endl;
	}

	return 0;
}
