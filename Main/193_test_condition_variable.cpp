/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：193_test_condition_variable.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年09月04日
*   描    述：简单测试C++11的条件变量与unique_lock配合使用
*   版    本: Version 1.00
*   编译指令: g++ -o main 193_test_condition_variable.cpp -std=c++11 -l pthread
================================================================*/

#include <iostream>
#include <memory>		// std::unique_lock & std::lock_guard 
#include <mutex>		// std::mutex
#include <thread>		// std::thread
#include <condition_variable>	// std::condition_variable
#include <atomic>		// std::atomic
#include <chrono>		// std::chrono
#include <ctime>		// localtime
#include <cstring>		// std::string

using namespace std;

std::mutex mtx;							// 全局锁
std::atomic<bool> bReady = { false };	// 原子变量
std::condition_variable cv;				// 条件变量

void excuteFunc(int val);		// 普通的条件变量wait测试
bool cv_full();					// 返回条件变量是否满足
std::string getCurrentSystemTime();

int main()
{
	cout << "main thread begin, time: " << getCurrentSystemTime() << endl;
	std::thread t1(excuteFunc, 10);

	std::this_thread::sleep_for(std::chrono::seconds(5));	// 主线程等待5秒之后再将条件变量置为true
	{
		std::lock_guard<std::mutex> lk(mtx);	// 主线程获取到锁,准备对数据进行更改
		cout << " main thread get the mtx! then set bReady = true!" << endl;
		bReady = true;
	}
	cv.notify_one();	// 主线程数据更改完毕,通知线程

	t1.join();

	return 0;
}

void excuteFunc(int val)
{
	cout << __func__ << " be called!" << endl;
	{
		std::unique_lock<std::mutex> lck(mtx);
		cout << __func__ << " get the mtx! time: " << getCurrentSystemTime() << endl;
		cv.wait(lck, cv_full);	// 执行wait的同时会自动释放mtx锁,所以主线程可以获取到mtx锁
		cout << __func__ << " condition be full, time: " << getCurrentSystemTime() << endl;
	}
}

bool cv_full()
{
	return bReady ? true : false;
}

std::string getCurrentSystemTime()
{
	auto tt = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	struct tm* ptm = localtime(&tt);
	char date[60] = {0};
	sprintf(date, "%d-%02d-%02d-%02d.%02d.%02d", (int)ptm->tm_year+1900, (int)ptm->tm_mon+1, (int)ptm->tm_mday, (int)ptm->tm_hour, (int)ptm->tm_min, (int)ptm->tm_sec);
	return std::string(date);
}
