/*================================================================
*   Copyright (C) 2018 Renleilei. All rights reserved.
*   
*   文件名称：045_double_ExclamatoryMark.cpp
*   创 建 者：Renleilei (renleilei@foxmail.com)
*   创建日期：2018年06月08日
*   描    述：//测试双感叹号(取反)的结果
*   版    本: Version 1.00
================================================================*/

#include <iostream>
#include <typeinfo>

using namespace std;

int main(int argc, char **argv)
{
	int num_01 = 10;

	cout << !!num_01 << endl;

	cout << typeid(num_01).name() << endl;;

	return 0;
}
