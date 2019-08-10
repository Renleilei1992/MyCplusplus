/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：162_test_ThreadTimerClass.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年08月11日
*   描    述：
*   版    本: Version 1.00
*	编译指令: g++ -o main 162_test_ThreadTimerClass.cpp -std=c++11 -l pthread
================================================================*/

#include "../include/ThreadTimerClass.h"
#include <iostream>

using namespace std;

int main()
{
	cout << "hello world!! thread_id:[" << std::this_thread::get_id()  << "]" << endl;

	ThreadTimerClass ttm1;
	ttm1.startThread(400);

	int timer1 = ttm1.startTimer(0, 1000, [](void *){
		cout << "timer1 be excuted! thread_id:[" << std::this_thread::get_id() << "]" << endl;
	});

	std::this_thread::sleep_for(std::chrono::microseconds(5000));

	ttm1.stopTimer(timer1);


	ttm1.stopThread();
	return 0;
}
