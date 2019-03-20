/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：089_tickStamp.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年01月16日
*   描    述：
*   版    本: Version 1.00
================================================================*/

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

using namespace std;

int main()
{
	struct timeval tv;
    gettimeofday(&tv,NULL);
    printf("second:%ld\n",tv.tv_sec);  //秒
    printf("millisecond:%ld\n",tv.tv_sec*1000 + tv.tv_usec/1000);  //毫秒
    printf("microsecond:%ld\n",tv.tv_sec*1000000 + tv.tv_usec);  //微秒

    sleep(3); // 为方便观看，让程序睡三秒后对比
    std::cout << "3s later:" << std::endl;

    gettimeofday(&tv,NULL);
    printf("second:%ld\n",tv.tv_sec);  //秒
    printf("millisecond:%ld\n",tv.tv_sec*1000 + tv.tv_usec/1000);  //毫秒
    printf("microsecond:%ld\n",tv.tv_sec*1000000 + tv.tv_usec);  //微秒

	long lTime_01 = tv.tv_sec*1000 + tv.tv_usec/1000;
	cout << "=====> lTime_01: " << lTime_01 << endl;
	cout << "=====> lTime_01/1000: " << lTime_01/1000 << endl;

	int i = 10991;
	cout << " i / 1000 = " << i/1000 <<endl;

	return 0;
}
