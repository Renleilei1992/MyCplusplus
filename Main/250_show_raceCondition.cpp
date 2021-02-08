/*================================================================
*   Copyright (C) 2020 Renleilei. All rights reserved.
*   
*   文件名称：250_show_raceCondition.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2020年12月17日
*   描    述：尝试展示出线程竞争的场景
*   版    本: Version 1.00
================================================================*/

#include <iostream>
#include <thread>
#include <chrono>

int i = 0;

// 线程执行函数: 对共享变量i自增1执行10000次
void threadFunc() {
	for (int n = 0; n < 10000; n++) {
		//std::this_thread::sleep_for(std::chrono::milliseconds(1));
		std::this_thread::yield();
		i++;
		if (i > 5000 && i < 5005) {
			std::cout << "i == 5000?? current now i = " << i << " thread id: " << std::this_thread::get_id() << std::endl;
		}
	}
}

// 主函数
int main() {

	std::cout << "Start All threads." << std::endl;
	
	// 创建线程
	std::thread t1(threadFunc);
	std::thread t2(threadFunc);

	// 等待线程执行完毕
	t1.join();
	t2.join();

	std::cout << "All threads joined." << std::endl;
	std::cout << "now i = " << i << std::endl;

	return 0;
}
