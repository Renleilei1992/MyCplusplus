/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：195_test_cv_notify.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年09月06日
*   描    述：测试C++11条件变量的通知 notify_one() 和 notify_all()区别
*   版    本: Version 1.00
*   编译指令: g++ -o main 195_test_cv_notify.cpp -std=c++11 -l pthread
================================================================*/

/*
	总结: 
			1, notify_one() 用于随机唤醒等待条件变量的线程中其中一个线程(据实验结果来看是最近一个join的线程);
			2, notify_all() 用于唤醒所有等待条件变量的线程;(根据实验结果来看其实是按顺序一个个唤醒,并不是精准的同时全部,涉及到解锁和加锁的处理);
*/


#include <iostream>
#include <condition_variable>
#include <thread>
#include <chrono>

using namespace std;

std::condition_variable cv;
std::mutex mtx;
int i = 0;

void waits(int idx) {
//	{																		// 这个花括号是为了测试此 lck 锁的生命周期, 如果析构之前睡眠, 会持续持有该锁, 如果析构之后睡眠, 则锁已经释放, 其他线程可以拿到该锁
	cout << __func__ << "::Thread#" << idx << " be created!" << endl;
	std::unique_lock<std::mutex> lck(mtx);
	cv.wait(lck, []{return i == 1;});										// wait操作会解锁lck锁, 阻塞当前线程
	cout << __func__ << "::Thread#" << idx << " finish waiting!" << endl;
//	}
	std::this_thread::sleep_for(std::chrono::seconds(1));					// 此行代码可以测试得出notify_all()其实是队列唤醒, 因为此处睡眠1s依旧持有mtx锁, 仅当作用域结束, lck析构后队列中的其它线程才会获取到锁并执行
}

void createThread();

void signals() {
	std::this_thread::sleep_for(std::chrono::seconds(3));
	{
		std::lock_guard<std::mutex> lck(mtx);
		i = 1;
	}
	cout << __func__ << "::notify one!" << endl;
	cv.notify_one();

	std::this_thread::sleep_for(std::chrono::seconds(3));
/*	{
		std::lock_guard<std::mutex> lck(mtx);
		i = 1;
	}*/
	cout << __func__ << "::notify all!" << endl;
	cv.notify_all();
}

int main()
{
	createThread();
	return 0;
}

void createThread()
{
	std::thread t1(waits, 1), t2(waits, 2), t3(waits, 3), t4(waits, 4), t5(waits, 5), t6(signals);
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();
}
