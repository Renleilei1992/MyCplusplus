/*================================================================
*   Copyright (C) 2020 Renleilei. All rights reserved.
*   
*   文件名称：251_test_multiThread.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2020年12月17日
*   描    述：
*   版    本: Version 1.00
================================================================*/


#include <iostream>		// std::cout, std::endl
#include <atomic>		// std::atomic, std::atomic_flag, ATOMIC_FLAG_INIT
#include <vector>		// std::vector
#include <thread>		// std::thread

using namespace std;

// 初始化一个 std::atomic<bool> 类型的原子变量
std::atomic<bool> ready(false);
std::atomic<bool> stop(false);
std::atomic_flag winner = ATOMIC_FLAG_INIT;	// 

int countNum = 0;

void do_count1m(int id);

int main()
{

	std::vector<std::thread> vec_threads;
	cout << "spawning 10 threads that count to 1 millon..." << endl;

	for (int i = 0; i < 10; ++i) {
		vec_threads.push_back(std::thread(do_count1m, i));
	}

	ready = true;

	for (auto & th : vec_threads) {
		if (th.joinable()) {
			th.join();
		}
	}

	return 0;
}

void do_count1m(int id)
{
	while (!ready) {
		std::this_thread::yield();	// 等待ready变为true
	}

	cout << __func__ << " ready is true!! id: " << id << endl;

	for (volatile int i = 0; i < 1000000; ++i) {
		// 计数

		// 如果有一个线程赢了, 其它线程需要结束.
		countNum = i;
		if(stop) {
			cout << "id: " << id << " my countNum: " << countNum << endl;
			return;
		}
	}

	// 最先执行的线程将会设置此winner flag并返回false;
	if (!winner.test_and_set()) {	// 如果atomic_flag对象被设置，则返回true; 如果atomic_flag对象未被设置，则设置之，返回false
		cout << "thread #" << id << " won!! countNum: " << countNum << endl;
		stop = true;
	}
}
