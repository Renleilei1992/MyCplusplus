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
	cout << getCurrentSystemTime() << __func__ << "::main thread begin! thread id: " << std::this_thread::get_id() << endl;
	std::thread t1(excuteFunc, 10);

	std::this_thread::sleep_for(std::chrono::seconds(5));	// 主线程等待5秒之后再将条件变量置为true
	{
		std::lock_guard<std::mutex> lk(mtx);	// 主线程获取到锁,准备对数据进行更改
		cout << getCurrentSystemTime() << __func__ << "::main thread get the mtx! then set bReady = true! thread id: " << std::this_thread::get_id() << endl;
		bReady = true;
		cv.notify_one();	// 主线程数据更改完毕,通知线程	// 此操作是异步操作,不会阻塞主线程(所以放在这个生命区间大括号里和放在大括号外是同样的结果!)
		std::this_thread::sleep_for(std::chrono::seconds(5));	// 主线程在通知其他线程之后仍旧再持有锁5秒再释放,测试结果显示子线程接收到notify通知但是由于没有拿到锁,依旧不会退出wait(),直到主线程释放锁之后子线程才会退出wait() (退出wait的时候会自动加锁))
	}

	t1.join();

	return 0;
}

void excuteFunc(int val)
{
	cout << getCurrentSystemTime() << __func__ << "::be called! thread id: " << std::this_thread::get_id() << endl;
	{
		std::unique_lock<std::mutex> lck(mtx);
		cout << getCurrentSystemTime() << __func__ << "::get the mtx!" << endl;
		cv.wait(lck, cv_full);	// 执行wait的同时会自动释放mtx锁,所以主线程可以获取到mtx锁	// 当wait()被通知时,会自动去获取mtx锁,wait()条件满足时仍旧是持有这个锁的,直到这个大括号生命周期结束才会析构掉lck对象的锁
		cout << getCurrentSystemTime() << __func__ << "::condition be full!" << endl;
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
	sprintf(date, "[%d-%02d-%02d-%02d.%02d.%02d] ", (int)ptm->tm_year+1900, (int)ptm->tm_mon+1, (int)ptm->tm_mday, (int)ptm->tm_hour, (int)ptm->tm_min, (int)ptm->tm_sec);
	return std::string(date);
}
