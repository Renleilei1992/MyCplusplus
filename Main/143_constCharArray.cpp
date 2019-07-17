/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：143_constCharArray.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年07月01日
*   描    述：
*   版    本: Version 1.00
*	编译指令: g++ -o main 143_constCharArray.cpp -std=c++11
================================================================*/

#include <iostream>

using namespace std;

void printArray(const char** charArray, int size);

int main()
{
	const char** cArray = new const char*[3];
	cArray[0] = "hello";
	cArray[1] = "world";
	cArray[2] = " !";

	printArray(cArray, 3);

	if (cArray != nullptr) {
		delete [] cArray;
	}

	return 0;
}

void printArray(const char** charArray, int size)
{
	if (charArray == nullptr) {
		cout << "it's a nullptr!" << endl;
		return;
	}

	cout << "size: " << size << endl;
	for (int i = 0; i < size; ++i) {
		cout << "数组元素[" << i << "] :" << charArray[i] << endl;
	}
}
