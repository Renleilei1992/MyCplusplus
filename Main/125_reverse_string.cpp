/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：125_reverse_string.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年05月07日
*   描    述：
*   版    本: Version 1.00
================================================================*/

#include <iostream>
#include <string.h>
#include <stack>

using namespace std;

void reverseStr(const string& str);
void reverseWord(const string& str);

int main()
{
	string str1 = "Hello World!";

	reverseStr(str1);
	reverseWord(str1);

	string str2(str1.rbegin(), str1.rend());
	cout << "取巧方法反转字符串结果: " << str2 << endl;

	return 0;
}

// 反转字符串,使用栈的特性
void reverseStr(const string& str)
{
	stack<char> strStack;
	for(int i = 0; i < str.length(); ++i) {
		cout << "str[" << i << "]: " << str[i] << endl;
		strStack.push(str[i]);
	}

	cout << "----- 翻转后的字符串为: ";
	while(!strStack.empty()) {
		cout << strStack.top();
		strStack.pop();
	}
	cout << endl;
}

// 反转单词
void reverseWord(const string& str)
{
	stack<string> strStack;
	string temp;
	for(int i = 0; i < str.length(); ++i) {
		if(str[i] == ' ') {
			strStack.push(temp);
			temp = "";
			strStack.push(string(" "));
		} else {
			temp += str[i];
			if(i == str.length() - 1) {
				strStack.push(temp);
				temp = "";
			}
		}
	}

	while(!strStack.empty()) {
		cout << strStack.top();
		strStack.pop();
	}
	cout << endl;
}
