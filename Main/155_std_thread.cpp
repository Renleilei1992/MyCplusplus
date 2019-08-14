/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：155_std_thread.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年08月07日
*   描    述：使用标准stl中的thread::hardware_concurrency() 函数获取当前CPU的物理核心数
*   版    本: Version 1.00
*	编译指令: g++ -o main 155_std_thread.cpp -std=c++11 -lpthread
*	参考文献: https://www.cnblogs.com/lidabo/p/7852033.html[C++11并发之std::thread]
*			  https://www.runoob.com/w3cnote/cpp-std-thread.html [菜鸟教程-std::thread]
================================================================*/

#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void foo();
void bar();
void test_join();
void test_join2();

int main()
{
	cout << "----> hello thead!" << endl;

	auto n = thread::hardware_concurrency();		// 获取CPU核心数
	cout << "----> cpu has [" << n << "] cores!" << endl;

	test_join();
	test_join2();

	return 0;
}

void foo()
{
	std::cout << __FUNCTION__ << "---> be called!" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));
}

void bar()
{
	std::cout << __FUNCTION__ << "---> be called!" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));
}

void test_join()
{
	// joinable: 检查线程是否可被 join。检查当前的线程对象是否表示了一个活动的执行线程，由默认构造函数创建的线程是不能被 join 的。
	// 另外，如果某个线程 已经执行完任务，但是没有被 join 的话，该线程依然会被认为是一个活动的执行线程，因此也是可以被 join 的
	std::cout << __FUNCTION__ << "---> be called!" << std::endl;
	std::thread t;
	std::cout << "before starting, joinable: " << t.joinable() << '\n';

	t = std::thread(foo);
	std::cout << "after starting, joinable: " << t.joinable() << '\n';

 	t.join();		// join: Join 线程，调用该函数会阻塞当前线程，直到由 *this 所标示的线程执行完毕 join 才返回
}

void test_join2()
{
	std::cout << __FUNCTION__ << "---> be called!" << std::endl;
	std::cout << "starting first helper...\n";
	std::thread helper1(foo);

	std::cout << "starting second helper...\n";
	std::thread helper2(bar);

	std::cout << "waiting for helpers to finish..." << std::endl;
	helper1.join();
	helper2.join();

	std::cout << "done!\n";
}
