/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：189_test_sizeof.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年08月29日
*   描    述：
*   版    本: Version 1.00
================================================================*/

#include <iostream>

using namespace std;

struct SomeType {
	int a;
	char b;
};
    
int main()
{
	cout << sizeof(SomeType::a) << " " << sizeof(SomeType::b) << endl;  // 直接由SomeType型別取得非静态成员的大小，C++03不行。C++11允許
	return 0;
}
