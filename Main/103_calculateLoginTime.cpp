/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：103_calculateLoginTime.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年04月25日
*   描    述：输入当日登入登出时间，计算出当日的登录时长
*   版    本: Version 1.00
================================================================*/

#include <iostream>
#include <time.h>
#include <cstdio>

using namespace std;

int main()
{
	int logInTime = 1556123000;
	int logOutTime = 1556123035;

	cout << "登录总时间为: " << (logOutTime - logInTime) << " 秒" << endl;

	cout << "---- 分割线 ----" << endl;

	time_t t1;
	time(&t1);
	t1 = t1 + 8*3600;
	tm* t = gmtime(&t1);
	cout << "use gmtime: " << t1 << endl;

	// man gmtime can see the struct time_t
	printf("%d-%02d-%02d %02d:%02d:%02d\n", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);

	return 0;
}
