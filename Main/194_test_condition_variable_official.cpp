/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：194_test_condition_variable_official.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年09月05日
*   描    述：使用官方的示例测试 std::condition_variable::wait 和 wait_for
*   版    本: Version 1.00
*   编译指令: g++ -o main 194_test_condition_variable_official.cpp -std=c++14 -l pthread -fext-numeric-literals
*   参考文献: std::condition_variable::wait() -> https://zh.cppreference.com/w/cpp/thread/condition_variable/wait
*             std::condition_variable::wait_for() -> https://zh.cppreference.com/w/cpp/thread/condition_variable/wait_for
================================================================*/

#include <iostream>
#include <thread>				// std::thread
#include <condition_variable>	// std::condition_variable
#include <chrono>				// std::chrono

using namespace std;
using namespace std::chrono_literals;		// std::this_thread::sleep_for(120ms)  编译指令变为 -std=c++14 -fext-numeric-literals

std::condition_variable cv;
std::mutex mtx;					// 此互斥锁三个目的: 1,同步到i的访问; 2,同步到cout的访问; 3,条件变量cv

int i = 0;

void testWaitFunc();
void testWaitForFunc();

/* 测试std::condition_variable::wait()的示例 */
void waits() {
	std::unique_lock<std::mutex> lk(mtx);
	cout << __func__ << "::waiting... id = [" << std::this_thread::get_id() << "]" << endl;
	cv.wait(lk, []{return i == 1;});
	cout << __func__ << "::finished waiting. i == 1 now -> id = [" << std::this_thread::get_id() << "]" << endl;
}

/* 测试std::condition_variable::wait_for()的示例 */
void waitsFor(int idx) {
	std::unique_lock<std::mutex> lck(mtx);
	cout << __func__ << "::thread#" << idx << "   waiting... id = [" << std::this_thread::get_id() << "]" << endl;
	if (cv.wait_for(lck, idx*100ms, []{return i == 1;})) {
		cout << __func__ << "::thread#" << idx << "   finished waiting. -> id = [" << std::this_thread::get_id() << "]" << endl;
	} else {
		cout << __func__ << "::thread#" << idx << "   timeout. -> id = [" << std::this_thread::get_id() << "]" << endl;
	}
}

/* 测试std::condition_variable:wait()
*  此函数会先睡眠1秒之后获取锁,但是不修改变量,通知到等待条件变量的线程(由于其他等待条件变量的线程会校验变量,仍旧会等待);
*  再次等待1秒之后获取锁,修改变量值,通知到所有等待条件变量的线程(变量修改后,都会通过校验,线程都会执行完毕)  
*/
void signals() {
	std::this_thread::sleep_for(std::chrono::seconds(1));
	{
		std::lock_guard<std::mutex> lk(mtx);
		cout << __func__ << "::notifying...  id = [" << std::this_thread::get_id() << "]" << endl;
	}
	cv.notify_all();

	std::this_thread::sleep_for(std::chrono::seconds(1));
	{
		std::lock_guard<std::mutex> lk(mtx);
		i = 1;
	}
	cout << __func__ << "::notifying again!  id = [" << std::this_thread::get_id() << "]" << endl;
	cv.notify_all();
}

/* 测试std::condition_variable::wait_for()
*  此函数会先睡眠120ms之后通知所有等待条件变量的线程, 此时由于变量未修改为1, 所以阻塞的线程不会进行下一步, 仍旧会等待;
*  线程t1由于设定的wait_for时间延迟为100ms, 超时后检测出该变量未修改(时间轴此时在120ms)
*  信号线程再次睡眠100ms之后更改变量为1后通知所有等待条件变量的线程, 此时由于变量已修改为1, 所以此时阻塞的线程会会校验条件变量;
*  线程t2由于设定的wait_for时间延迟为200ms, 超时后检测出该变量未修改(时间轴此时在220ms)
*  线程t3由于设定的wait_for时间延迟为300ms, 还未超时, 此时接到notify后校验条件变量已修改为1, 所以不再等待(时间轴此时在220ms) // 要观察现象可以将t3设置为30*100ms延迟
*/
void signals_waitFor() {
	std::this_thread::sleep_for(120ms);
	cout << __func__ << "::notifying... id = [" << std::this_thread::get_id() << "]" << endl;
	cv.notify_all();
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	{
		std::lock_guard<std::mutex> lck(mtx);
		i = 1;
	}
	cout << __func__ << "::notifying again!  id = [" << std::this_thread::get_id() << "]" << endl;
	cv.notify_all();
}

int main()
{
//	testWaitFunc();
	testWaitForFunc();
	return 0;
}

void testWaitFunc()
{
	std::thread t1(waits), t2(waits), t3(waits), t4(signals);
	t1.join();
	t2.join();
	t3.join();
	t4.join();
}

void testWaitForFunc()
{
	std::thread t1(waitsFor, 1), t2(waitsFor, 2), t3(waitsFor, 3), t4(signals_waitFor);
	t1.join();
	t2.join();
	t3.join();
	t4.join();
}
