/*================================================================
*   Copyright (C) 2020 Renleilei. All rights reserved.
*   
*   文件名称：234_search_string.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2020年05月29日
*   描    述：需求: 先后输入两串字符串, 字符串长度不超过100, 在后输入的字符串中搜索有没有前一串字符
*   版    本: Version 1.00
*   编译指令: 1, gcc -o main 234_search_string.cpp
			  2, g++ -o main 234_search_string.cpp -std=c++11
			  3, g++ -o main 234_search_string.cpp -std=c++17 (当前系统的g++版本暂不支持C++17)
================================================================*/

//#define _C_STRSTR_	// 使用C语言的strstr函数进行查找
#define _CPP_FIND_  // 使用C++标准库中的string::find函数查找
//#define _CPP_BOYER_MOORE_HASHPOOL_	// 使用C++ 17 的KMP算法中的 bm/bmh 算法

#ifdef _C_STRSTR_
#include <stdio.h>
#include <string.h>

int main(void)
{
	char a[101], b [101];
	scanf("%s%s", a, b);
	
	const char* p = strstr(b, a);
	puts(p == NULL ? "1,不存在!":"1,存在");
	return 0;
}


#elif defined(_CPP_FIND_)
#include <iostream>
#include <string>
using namespace std;

int main(void)
{
	string a, b;
	cin >> a >> b;

	size_t index = b.find(a);
	cout << (index == string::npos ? "2,不存在":"2,存在") << endl;

	std::string str("测试中文string输入是否正常!!");
	cout << str << endl;
	return 0;
}

#elif defined(_CPP_BOYER_MOORE_HASHPOOL_)
#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
using namespace std;

int main(void)
{
	string a, b;
	cin >> a >> b;

	auto itor = std::search(b.begin(), b.end(), std::boyer_moore_horspool_searcher(a.begin(), a.end()));
	cout << (itor == b.end() ? "3,不存在":"3,存在")  << endl;
	retrun 0;
}

#endif
