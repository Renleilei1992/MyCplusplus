/*================================================================
*   Copyright (C) 2018 Renleilei. All rights reserved.
*   
*   文件名称：069_getLocalSystemTime.cpp
*   创 建 者：Renleilei (renleilei@foxmail.com)
*   创建日期：2018年07月24日
*   描    述：
*   版    本: Version 1.00
================================================================*/

#include <iostream>
#include <ctime>
#include <cstdint>

using namespace std;

int main()
{
	time_t now_time;
	now_time = time(NULL);

	int32_t uCurLocalTime = static_cast<int32_t>(now_time);
	int32_t uCurServerTime = 1532396771;

	int32_t uOverTimeSeconds = abs(uCurServerTime - uCurLocalTime);
	cout << now_time << endl;
	cout << "uCurLocalTime:       [" << uCurLocalTime << "]" << endl;
	cout << "uCurServerTime:      [" << uCurServerTime << "]" << endl;
	cout << "uCurOverTimeSeconds: [" << uOverTimeSeconds << "]" << endl;

	return 0;
}
