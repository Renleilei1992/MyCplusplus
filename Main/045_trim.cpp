/*================================================================
*   Copyright (C) 2018 Renleilei. All rights reserved.
*   
*   文件名称：045_trim.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2018年04月24日
*   描    述：
*   版    本: Version 1.00
*   编译命令: 
================================================================*/

#include <iostream>
#include <string>
//#include <boost/algorithm/string.hpp>

using namespace std;
//using namespace boost;


std::string& trim_self(std::string &str);

int main()
{

	string str01 = "   hello world! ";
	string str02 = "   ";
	trim_self(str01);
	trim_self(str02);

	cout<<str01<<endl;
	cout<<str02<<endl;

	return 0;
}

std::string& trim_self(std::string &str)
{
	if(str.empty())
	{
		cout<<"it's empty!"<<endl;
		return str;
	}

	str.erase(0, str.find_first_not_of(" "));
	cout<<"earse left end, now the string is: ["<<str<<"]"<<endl;
	str.erase(str.find_last_not_of(" ") + 1);
	cout<<"earse right end, now the string is: ["<<str<<"]"<<endl;

	return str;
}
