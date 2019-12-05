/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：223_interview_consumer_producer_model.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年12月05日
*   描    述：
*   版    本: Version 1.00
================================================================*/

#include <iostream>
#include <thread>				// std::thread  std::this_thread
#include <condition_variable>	// std::condition_variable
#include <memory>				// std::shared_ptr std::unique_ptr std::weak_ptr std::unique_lock & std::lock_guard 
#include <queue>				// std::queue
#include <chrono>				// std::chrono::seconds(5)
#include <atomic>

#define _MAX_QUEUE_SIZE 20

using namespace std;

std::queue<int>	q;
std::mutex mtx;
std::condition_variable producer_cv, consumer_cv;

std::atomic<int> atom_NUM = { 100 };

void consumerFunc()
{
	cout << __func__ << " begin consume!!" << endl;
	while(true) {
		std::this_thread::sleep_for(std::chrono::seconds(3));
		std::unique_lock<mutex>	lck(mtx);
		while(q.size() == 0) {
			consumer_cv.wait(lck);			// 等待锁至while条件不满足
		}

		q.pop();
		cout << __func__ << "::consumer id: " << std::this_thread::get_id() << " q.size: " << q.size() << "  当前任务队列头部任务编号: " << q.front() << endl;

		producer_cv.notify_all();
	}
}

void producerFunc()
{
	cout << __func__ << " begin produce!!" << endl;
	while(true) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		std::unique_lock<mutex> lck(mtx);
		while(q.size() == _MAX_QUEUE_SIZE) {
			producer_cv.wait(lck);			// 等待锁至while条件不满足
		}
		
		q.push(atom_NUM);
		atom_NUM++;
		cout << __func__ << "::producer id: " << std::this_thread::get_id() << " q.size: " << q.size() << " 当前任务队列尾部任务编号: " << q.back() << endl;
		
		consumer_cv.notify_all();
	}
}

int main()
{
	std::thread t1(producerFunc);
	std::thread t2(consumerFunc);
	std::thread t3(consumerFunc);
	
	//std::this_thread::sleep_for(std::chrono::seconds(20));
	if (t1.joinable()) {
		cout << "t1 join!!" << endl;
		t1.join();
	}
	cout << "t2 join!!" << endl;
	if (t2.joinable()) {
		cout << "t2 join!!" << endl;
		t2.join();
	}
	return 0;
}
