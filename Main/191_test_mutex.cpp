/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：191_test_mutex.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年09月03日
*   描    述：用于简单测试C++11的多线程和锁
*   版    本: Version 1.00
*   编译指令: g++ -o main 191_test_mutex.cpp -std=c++11 -l pthread
================================================================*/

#include <iostream>
#include <thread>	// std::thread
#include <chrono>	// std::chrono
#include <mutex>	// std::mutex
#include <memory>	// std::lock_guard  or  std::unique_lock
#include <vector>

using namespace std;

std::mutex mtx;

void func(int a);
void testThreadFunc();



int main()
{
	testThreadFunc();
	return 0;
}

void func(int a)
{
	{
		cout << a << __func__ << "::waiting for the mutex!" << endl;
		std::lock_guard<std::mutex> lck(mtx);	// 进入作用域, 构造函数获得mtx锁
		cout << a << __func__ << "::get the mutex! thread func be called! a: " << a << " thread id: " << std::this_thread::get_id() << endl;
		std::this_thread::sleep_for(std::chrono::seconds(3));
	}
	// 离开作用域，析构函数会释放mtx锁
}

void testThreadFunc()
{
	std::vector<std::thread> threadVec;
	{
		std::lock_guard<std::mutex> lck(mtx);	// 进入作用域，构造函数获取mtx锁
		std::thread t1(func, 1);				// 创建线程t1	// 线程对象没办法直接push_back进容器;	需要使用std::move
		std::thread t2(func, 2);				// 创建线程t2	// 线程对象没办法直接push_back进容器;	需要使用std::move
		threadVec.emplace_back(std::move(t1));	// 推荐使用此方式存储到容器中, emplace_back可以减少push_back的额外复制和移动操作
		threadVec.emplace_back(std::move(t2));
//		t1.detach();
		cout << __func__ << " main thread will release the mutex rightnow! main thread id: " << std::this_thread::get_id() << endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	// 离开作用域, 析构函数会释放mtx锁
	
	for (auto &it : threadVec) {
		if (it.joinable()) {
			it.join();		// 只有上面的作用域离开，lock_guard 析构后才会释放mtx锁	线程才会获取到mtx
		}
	}
	cout << __func__ << " main thread will sleep for 5 seconds for the thread working! main thread id: " << std::this_thread::get_id() << endl;
	std::this_thread::sleep_for(std::chrono::seconds(5));
}
