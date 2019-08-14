/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：161_cpp_yield.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年08月10日
*   描    述：std::this_thread::yield -> 当前线程立刻释放CPU时间片 sleep_for 会线程休眠(不竞争CPU),等待一段时间后立刻参与CPU竞争
*   版    本: Version 1.00
*	编译指令: g++ -o main 161_cpp_yield.cpp -std=c++11
================================================================*/

#include <iostream>
#include <chrono>
#include <thread>
 
// "busy sleep" while suggesting that other threads run 
// for a small amount of time
void little_sleep(std::chrono::microseconds us)
{
    auto start = std::chrono::high_resolution_clock::now();
    auto end = start + us;
    do {
       // std::this_thread::yield();		// output: 279 or 378 or 一个大于100的值
		std::this_thread::sleep_for(std::chrono::microseconds(100));
    } while (std::chrono::high_resolution_clock::now() < end);
}
 
int main()
{
    auto start = std::chrono::high_resolution_clock::now();
 
    little_sleep(std::chrono::microseconds(100));
 
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    std::cout << "waited for "
              << std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count()
              << " microseconds\n";
}

// 总结: 
// 1, sleep_for 会将线程休眠(其实是进入休眠线程，结束之后会插入调度队列(若睡眠时间小于时间片会跳过该时间片)) -> 总之CPU负载较大;
// 2, yeild     会将线程时间片立刻释放，等待其他线程执行完毕之后再竞争CPU，不会造成CPU额外负载;
