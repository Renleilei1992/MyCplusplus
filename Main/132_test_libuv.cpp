/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：132_test_libuv.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年05月10日
*   描    述：
*   版    本: Version 1.00
*   编译指令: g++ -o main 132_test_libuv.cpp -g -Wall -luv ../libs/libuv.a
================================================================*/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "../include/uv.h"

using namespace std;

int main()
{
	//uv_loop_t *loop = malloc(sizeof(uv_loop_t));	// malloc 需要转换类型,编译器不认
	uv_loop_t *loop = (uv_loop_t *)malloc(sizeof(uv_loop_t));
	uv_loop_init(loop);

	printf("Now quitting.\n");
	uv_run(loop, UV_RUN_DEFAULT);

	uv_loop_close(loop);
	free(loop);
	return 0;
}
