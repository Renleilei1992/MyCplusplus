/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：151_test_ThreadTimer.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年08月04日
*   描    述：简单使用一个c11特性的线程安全timer测试
*   版    本: Version 1.00
================================================================*/

#include <iostream>
#include "../include/ThreadTimer.h"

using namespace std;

int main(int argc, char** argv)
{
	ThreadTimer ttm;
	cout << "start thread ...\n" << endl;
	
	// test delay timer
	cout << "start delay timer 5 2 \n" << endl;
	int timer1 = ttm.startTimer(5000, 2000, [](void*){
		cout << "delay taimer 5 2 lambda be called!" << endl;
	});

	// test normal timer
	cout << "start normal timer 0 1 \n" << endl;
	int timer2 = ttm.startTimer(0, 1000, [](void*){
		cout << "normal timer 0 1 lambda be called!" << endl;
	});

	std::this_thread::sleep_for(std::chrono::seconds(20));

	
	ttm.stopTimer(timer1);
	cout << "stop delay timer 5 2 \n" << endl;

	ttm.stopTimer(timer2);
	cout << "stop normal timer 0 1 \n" << endl;

	ttm.stopThread();
	cout << "stop thread!! \n" << endl;

	cout << "success!\n " << endl;


	return 0;
}
