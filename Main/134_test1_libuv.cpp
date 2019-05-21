/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：134_test1_libuv.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年05月10日
*   描    述：
*   版    本: Version 1.00
*   编译指令: g++ -o main 134_test1_libuv.cpp -g -Wall -luv ../libs/libuv.a
================================================================*/

// https://windyx.com/blog?id=12

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include "../include/uv.h"

using namespace std;

void doing_work(uv_work_t *req);
void after_doing_work(uv_work_t *req, int status);

int main()
{
	uv_work_t* work = (uv_work_t*)malloc(sizeof(uv_work_t));

	// post task
	uv_queue_work(uv_default_loop(), work, doing_work, after_doing_work);

	// run loop
	uv_run(uv_default_loop(), UV_RUN_DEFAULT);
	return 0;
}


void doing_work(uv_work_t *req)
{
	cout << "doing_work()-----" << endl;
	sleep(3);
	double i = 20434.00 / 1024;
	cout << "doing_work(): i = " << i << endl;
	long j = 58045249;
	long k = 524288000;
	cout << "doing_work(): result(58045249/524288000) = " << j / k * 100 << endl;

	// event 3
	cout << "1 << 20 = " << (1 << 20) << endl;
	cout << "1024 * 1024 = " << 1024 * 1024 << endl;
}

void after_doing_work(uv_work_t *req, int status)
{
	cout << "after_doing_work()-----" << endl;
}
