/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：170_std_shared_ptr.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年08月16日
*   描    述：
*   版    本: Version 1.00
*	参考博客: https://blog.csdn.net/qq_34992845/article/details/69218843
*	编译指令: g++ -o main 170_std_shared_ptr.cpp -std=c++11 -l pthread
================================================================*/

/*
总结:
	1, shared_ptr 注意可以采用make_shared<string> 这种安全点的方式	// 参考链接: https://zh.cppreference.com/w/cpp/memory/shared_ptr/make_shared
		- std::shared_ptr<T>(new T(args...)) 的替代品, 此方式为至少二次分配, 一次为T一次为共享指针的控制块
		- std::shared_ptr<T>(new T(args...)) 可能调用T的非公开构造函数(在其可访问的场景执行时), 而make_shared则要求仅使用公开的构造函数
		- make_shared 不会使用重载的new操作符
	2, std::thread t1(func, args);		// 线程对象在构造完毕后将立即开始执行(等待OS的调度延迟)
		- t1.detach()					// 线程对象创建完毕后立即调用将会分离当前现象与创建出的线程,新创建出的线程将作为后台线程执行, 创建的线程死活与当前线程无关, 它的资源会被init进程回收
		- t1.join()						// 不同于detach, join操作需要找到合适的时机对线程对象使用, 阻塞当前线程, 直至*this所标识的线程完成其执行;

*/


#include <iostream>		// std::cout  std::endl
#include <memory>		// std::shared_ptr  std::weak_ptr std::unique_ptr
#include <cstring>		// std::string
#include <thread>		// std::thread
#include <chrono>		// std::chrono::seconds
#include <mutex>		// std::mutex
#include <condition_variable>	// std::condition_variable
#include <atomic>		// std::atomic
using namespace std;

std::mutex ptrMtx;
std::condition_variable cv;
std::atomic<bool> bUsedFlag = { false };

class A
{
public:
	A() { cout << __func__ << "A()" << endl; }
	~A() { cout << __func__ << "~A()" << endl; }

	void func_A() { cout << __func__ << "A::func_A() be called!" << endl; }
};


void checkPtr(std::shared_ptr<int> ptr);
void initStdSharedPtr();
void testStdSharedPtr();
void testStdSharedPtr_weakPtr();
void checkWeakPtr(std::weak_ptr<A> ptr);
bool shipment_available();
void testThread_join();

int main()
{
//	initStdSharedPtr();
//	testStdSharedPtr();
//	testStdSharedPtr_weakPtr();
	testThread_join();
	return 0;
}

bool shipment_available()
{
	return bUsedFlag;
}

void checkPtr(std::shared_ptr<int> ptr)
{
	if (ptr) {
		std::cout << __func__ << "*ptr = " << *ptr << std::endl;
	} else {
		std::cout << __func__ << "ptr is a invalid pointer!!" << std::endl;
	}
}

void checkWeakPtr(std::weak_ptr<A> ptr)
{
	{
		std::unique_lock<std::mutex> lck(ptrMtx);
		shared_ptr<A> tmpPtr = ptr.lock();
		if(tmpPtr != nullptr) {
			cout << __func__ << " id: " << std::this_thread::get_id() << " ptr<A>.func_A(): ";
			tmpPtr->func_A();
		} else {
			cout << __func__ << " id: " << std::this_thread::get_id() << " ptr<A> is a invalid pointer!!" << endl;
		}
	
		bUsedFlag = true;
		cout << __func__ << " id: " << std::this_thread::get_id() << " prepare to notify the cv status!!" << endl;
		std::this_thread::sleep_for(std::chrono::seconds(5));
		cv.notify_one();
		cout << __func__ << " id: " << std::this_thread::get_id() << " notify the cv status end!!" << endl;
//		cargo++;
	}
}

void initStdSharedPtr()
{
	// 空指针
	shared_ptr<int> p1;
	if (p1) {
		cout << __func__ << " p1 is a nullptr!!" << endl;
	}

	// 初始化字符串指针
	shared_ptr<string> p2(new string);
	if (p2 && p2->empty()) {
		*p2 = "hello world";
		cout << *p2 << " p2's refs: " << p2.use_count() << endl;
	}
	p2.reset();

	// 一般的安全初始化方式
	shared_ptr<string> p3(new string("normal mode create ptr!"));
	cout << "normal mode create shared_ptr usage! p3: " << *p3 << " p3.use_count(): " << p3.use_count() << endl;
	p3.reset();

	// 建议的安全的初始化方式
	shared_ptr<string> p4 = make_shared<string>("safe mode create shared_ptr");
	cout << "safe mode create shared_ptr usage! p4: " << *p4  << "p4.use_count(): " << p4.use_count() << endl;
	p4.reset();

}

void testStdSharedPtr()
{
	shared_ptr<int> sp1(new int(10));	
	shared_ptr<int> sp2(new int(99));
	shared_ptr<int> sp3(sp1);	
	shared_ptr<int> sp4;

	sp4 = sp1;

	cout << "sp1: " << *sp1 << endl;
	cout << "sp2: " << *sp2 << endl;
	cout << "sp3: " << *sp3 << endl;
	cout << "sp4: " << *sp4 << endl;

	cout << "count1: " << sp1.use_count() << endl;
	sp4.reset();
	cout << "count2: " << sp1.use_count() << endl;
	sp3.reset();
	cout << "count3: " << sp1.use_count() << endl;
	sp1.reset();
	cout << "count4: " << sp1.use_count() << endl;

	checkPtr(sp1);
}

void testStdSharedPtr_weakPtr()
{
	bUsedFlag = false;
	cout << __func__ << " thread id: " << std::this_thread::get_id() << endl;
	{
		shared_ptr<A> p(new A());
		std::thread t1(checkWeakPtr, weak_ptr<A>(p));
//		t1.detach();									// detach实在线程被创建之后立刻调用, 用于把被创建的线程和当前线程分离, 分离的线程则变为后台线程, 创建的线程死活与当前线程无关, 它的资源会被init进程回收
		std::unique_lock<std::mutex> lck(ptrMtx);
		cv.wait(lck, shipment_available);
		cout << __func__ << " shipment is available, now can reset the ptr!  is thread joinable?? [" << t1.joinable() << "]" << endl;
		p.reset();
//		cout << "*this" << *this << endl;
		t1.join();		// if not do this, will catch a exception: terminate called without an active exception	// join操作是在线程创建后的某个合适的时机进行调用, 回收对应创建的线程的资源, 避免造成资源泄露;
		cout << "now is joinable?? [" << t1.joinable() << "]" << endl;
	}

	bUsedFlag = true;
	std::this_thread::sleep_for(std::chrono::seconds(3));
}

void testThread_join()
{
	cout << __func__ << "---> be called! thread id: [" << std::this_thread::get_id() << "]" << endl;

	std::thread t1([](){
		cout << __func__ << " thread id: [" << std::this_thread::get_id() << "] before sleep!" << endl;
		std::this_thread::sleep_for(std::chrono::seconds(3));
		cout << __func__ << " thread id: [" << std::this_thread::get_id() << "] after sleep!" << endl;
	});

	cout << __func__ << " thread id: [" << std::this_thread::get_id() << "] before join!" << endl;
	t1.join();
	cout << __func__ << " thread id: [" << std::this_thread::get_id() << "] after join!" << endl;
}
