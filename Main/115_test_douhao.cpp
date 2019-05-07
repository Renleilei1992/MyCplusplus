/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：115_test_douhao.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年05月05日
*   描    述：测试一个关于逗号的写法
*   版    本: Version 1.00
================================================================*/

#include <iostream>

using namespace std;

int main()
{
	int ret = 1;
	for (int i = 0; i < 5; ++i) {
		cout << "----A ret = " << ret << "  i = " << i << endl;;
		ret += i, i+1;
		cout << "----b ret = " << ret << "  i = " << i << endl;;
	}

	return 0;
}
