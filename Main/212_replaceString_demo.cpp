/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：212_test.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年11月03日
*   描    述：简单测试一个字符串替换的demo
*   版    本: Version 1.00
================================================================*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Base
{
public:
	virtual void fun() { cout << "Base::fun" << endl;}
};

class Der : public Base
{
public:
	virtual void fun() final { cout << "Der::fun" <<endl; }
};

void printSize(char c[]);
void printSize_1(char c[100]);

std::string replaceSpace(string s) {
        std::ios::sync_with_stdio(false);   // 减少执行用时
        std::string strResult = "";
        std::string strSpace = " ";
        std::vector<char> vec;
        for (int i = 0; i < s.length(); ++i) {
            char tempChar[1] = "";
            tempChar[0] = s[i];
            std::string tempStr(tempChar);
            if (tempStr == strSpace) {
                strResult += "%20";
            } else {
                strResult += s[i];
            }
        }

        return strResult;
}

int main()
{
	Der d1;
	Base* b1 = &d1;

//	b1 = &d1;
	b1->fun();

	char c[] = "welcome to huawei test";
	cout << "size: " << sizeof(c) << endl;
	printSize(c);

	char c1[100] = {};
	printSize_1(c1);

	std::cout << "----------------" << endl;
	std::cout << replaceSpace(std::string("we are happy.")) << endl;
	return 0;
}

void printSize(char c[])
{
	cout << __func__ << "::size: " << sizeof(c) << endl;
}

void printSize_1(char c[100])
{
	cout << __func__ << "::1size: " << sizeof(c) << endl;
}
