/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：190_thread_guard.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年09月02日
*   描    述：资源获取即初始化RAII方式 一个比较好的处理线程join的方法
*   版    本: Version 1.00
================================================================*/

#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void func();

class Thread_guard
{
	std::thread &t;
public:
	explicit Thread_guard(std::thread& _t) : t(_t) {}
	~Thread_guard() {
		cout << __func__ << endl;
		if (t.joinable()) {
			t.join();
		}
	}

	Thread_guard(const Thread_guard& ) = delete;			// 屏蔽默认拷贝构造函数
	Thread_guard& operator=(const Thread_guard&) = delete;	// 屏蔽默认赋值运算符
};


int main()
{
	cout << "program begin! main thread id: " << std::this_thread::get_id() << endl;
	func();
	std::this_thread::sleep_for(std::chrono::seconds(3));
	cout << "program end!" << endl;
	return 0;
}

void func()
{
	std::thread t([]{
		cout << "thread be create!! id: " << std::this_thread::get_id() << endl;
	});

	Thread_guard g(t);
}
