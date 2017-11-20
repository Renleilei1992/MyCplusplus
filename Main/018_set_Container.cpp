/*================================================================
*   Copyright (C) 2017 Renleilei. All rights reserved.
*   
*   文件名称：018_set_Container.cpp
*   创 建 者：Renleilei (renleilei@foxmail.com)
*   创建日期：2017年11月16日
*   描    述：
*   版    本: Version 1.00
*   编译方法: g++ -o main 018_set_Container.cpp -I ../include/ -g -Wall -O3
================================================================*/


#include "018_student.h"

int main(int argc, char *argv[])
{
	int id_1 = 1001;
	const char name_1[] = "peter";

	/* 1. 字符数组 */
	char str1[] = "Hello World!";
	/* 2. 指针     */
	char str2   = "Hello C/C++!";
	/* 3. 宏定义   */
//	#define str3 "Hello World!";


	Student stu;
	stu.name = &name_1;
	stu.id = id_1;

	stu.introduce();

	return 0;
}

