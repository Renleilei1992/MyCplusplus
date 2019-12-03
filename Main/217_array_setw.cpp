/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：217_array_setw.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年12月02日
*   描    述：简单测试和使用了数组的 setw 格式化输出方法
*   版    本: Version 1.00
================================================================*/

#include <iostream>
using namespace std;

#include <iomanip>
using std::setw;

int main()
{
	int n[10]; 	// 包含10个整数的数组
	
	// 初始化数组元素
	for (int i = 0; i < 10; i++) {
		n[i] = i + 100;		// 设元素i的值为 i+100;
	}

	cout << "Element" << setw(13) << "Value" << endl;

	for (int j = 0; j < 10; j++) {
		cout << setw(7) << j << setw(13) << n[j] << endl;
	}

	return 0;
}
