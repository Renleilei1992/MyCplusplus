/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：160_cpp_mutex.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年08月10日
*   描    述：
*   版    本: Version 1.00
*	编译指令: g++ -o main 160_cpp_mutex.cpp -std=c++11 -l pthread
================================================================*/

// condition_variable::wait (with predicate)
#include <iostream>           // std::cout
#include <thread>             // std::thread, std::this_thread::yield
#include <mutex>              // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable
#include <chrono>

std::mutex mtx;
std::condition_variable cv;		// 条件变量

int cargo = 0;

bool shipment_available() {
	return cargo!=0;
}

void consume (int n) {
  for (int i=0; i<n; ++i) {
    std::unique_lock<std::mutex> lck(mtx);
    cv.wait(lck,shipment_available);
	std::chrono::milliseconds realTick = std::chrono::milliseconds(i*100);
	cv.wait_for(lck, realTick);
    // consume:
    std::cout << cargo << "  realTick[" << realTick.count() << "] this_thread id[" << std::this_thread::get_id() << "]" << std::endl;
    cargo=0;
  }
}

int main ()
{
  std::thread consumer_thread(consume,10);

  // produce 10 items when needed:
  for (int i=0; i<10; ++i) {
    while (shipment_available()) {
	//	 std::cout << "-------> shipment available true!! threadID[" << std::this_thread::get_id() << "]" << std::endl;
		 std::this_thread::yield();
	}
    std::unique_lock<std::mutex> lck(mtx);
    cargo = i+1;
	std::cout << "notify_one!! current threadID[" << std::this_thread::get_id() << "]" << std::endl;
    cv.notify_one();
  }

  consumer_thread.join();

  return 0;
}
