#include "ThreadTimerClass.h"
#include <iostream>

void ThreadTimerClass::startThread(int tick)
{
	if (m_timerThread)
	{
		// 如果定时器线程已启动，则不再重复启动
		return;
	}

	if (tick <= 0)
	{
		// 当传入的最小精度小于等于0时，默认将最小精度设置为500ms
		tick = 500;
	}

	m_tick = std::chrono::milliseconds(tick);
	m_timerThread = new std::thread(&ThreadTimerClass::threadProc, this);
	std::cout << __FUNCTION__ << "---------> be called! thead id: " << m_timerThread << std::endl;
}

void ThreadTimerClass::stopThread()
{
	if (!m_timerThread) {
		return;
	}

	m_bQuitFlag = true;

	{
		// 1, 作用域{}内构造一把锁, 离开该作用域会自动释放
		// 2, 通知使用 m_waitCond 的线程
		std::unique_lock<std::mutex> lock(m_waitConMutex);
		m_waitCond.notify_one();
	}

	// 主线程等待子进程期间什么都不能做。thread::join()会清理子线程相关的内存空间，此后thread object将不再和这个子线程相关了，即thread object不再joinable了
	// 所以join对于一个子线程来说只可以被调用一
	// 为了实现更精细的线程等待机制，可以使用***条件变量等***机制
	m_timerThread->join();
	delete m_timerThread;
	m_timerThread = nullptr;
	std::cout << __FUNCTION__ << "---------> be called! thead id: " << m_timerThread << std::endl;
}

int ThreadTimerClass::startTimer(int delay, int interval, std::function<void(void*)> cb, void* params)
{
	if (!m_timerThread || delay < 0 || interval <= 0 || !cb)
	{
		return -1;
	}

	// 构造一把条件变量锁，在startTimer作用域结束时才会释放(或者被 m_waitCond.notify_one() or m_waitCond.notify_all()唤醒)
	std::unique_lock<std::mutex> lock(m_waitConMutex);
	int timerID = m_timerID++;
	if (m_timerID >= 999999)
	{
		assert(0);
		return -1;
	}

	// 将定时器节点存入定时器线程的vector容器中
	TimerNode node(timerID, delay, interval, cb, params);
	m_timers.push_back(node);

	std::cout << __FUNCTION__ << "---------> timer start!! delay[" << delay << "] interval[" << interval << "]" << std::endl;

	return timerID;
}

void ThreadTimerClass::stopTimer(int id)
{
	if (!m_timerThread || id < 0 || id > 999999)
	{
		return;
	}

	// 检查当前线程id是否和定时器线程id相同
	if (std::this_thread::get_id() == m_timerThread->get_id())
	{
		std::cout << __FUNCTION__ << "---------> same thread id! current thead id[" << std::this_thread::get_id() << "] timerThread id: [" << m_timerThread << "]" << std::endl;
		std::unique_lock<std::mutex> lock(m_waitConMutex);
		for (auto iVec : m_timers)
		{
			if (iVec.m_id == id)
			{
				iVec.m_deleteLater = true;
				break;
			}
		}
	}
	else
	{
		std::cout << __FUNCTION__ << "---------> diff thread id! current thead id[" << std::this_thread::get_id() << "] timerThread id: [" << m_timerThread << "]" << std::endl;
		std::unique_lock<std::mutex> lock(m_waitConMutex);
		std::unique_lock<std::mutex> lockOut(m_outTimersMutex);
		for (auto iVec : m_timers)
		{
			if (iVec.m_id == id)
			{
				iVec.m_deleteLater = true;
				break;
			}
		}
	}
}

void ThreadTimerClass::threadProc()
{
	// 此函数为定时器线程的回调函数
	std::cout << __FUNCTION__ << "---->1 be called! thead id[ " << std::this_thread::get_id() << "] m_tick[" << m_tick.count() << "]" << std::endl;
	//std::this_thread::sleep_for(std::chrono::milliseconds(3000));
	//std::cout << __FUNCTION__ << "---->2 be called! thead id: " << std::this_thread::get_id() << std::endl;

	while (!m_bQuitFlag)
	{
		tick();
		{
			/*
			*	加锁，离开{}作用域后锁释放
			*	本质: 
			*		1, std::unique_lock<std::mutex> 这个类在构造 lock 对象时，调用了 m_waitConMutex->lock() 方法
			*		2, lock对象在离开{}作用域时发生析构会调用 m_waitConMutex->unlock() 方法释放锁
			*	如此使用的原因(避开直接手动调用lock()和unlock()):
			*		1, 如果手动使用lock()和unlock()，若其中的代码出现问题，则会造成无法正常unlock释放资源
			*	c++11 特性解析:
			*		1, c++11新增了四种锁(互斥对象): (1) std::mutex 普通互斥锁; (2) std::timed_mutex 带有超时机制的互斥锁; (3) std::recursive_mutex 允许被同一线程递归的lock和unlock锁; (4) std::recursive_timed_mutex 超时机制
			*		2, c++ 使用标准库提供的互斥对象管理类模板: (1)std::lock_guard; (2)std::unique_lock; (3)std::shared_lcok(c++14);
			*		3, lock_guard 与 unique_lock 其实内部构造一致, unique_lock 更为灵活, 均可以指定构造时是否加锁
			*		4, 互斥对象管理类模板的4中加锁策略: (1)默认 请求锁,阻塞当前线程直至成功获得锁; (2)std::defer_lock 不请求锁; (3)std::try_to_lock 尝试请求锁,但不阻塞线程,锁不可用时也会立即返回; (4)std::adopt_lock 假使当前线程已经获得互斥对象的所有权, 所以不再请求锁;
			*/
			std::unique_lock<std::mutex> lock(m_waitConMutex);
			std::cout << __FUNCTION__ << "---->2 be called! thread id: " << std::this_thread::get_id() << " get lock??[" << (lock.owns_lock() == true) << "]" << std::endl;
			std::chrono::milliseconds realTick = m_tick - m_consume;

			/**
			*   1, std::condition_variable::wait_for() 可以指定一个时间段，在当前线程收到通知或者指定的时间 realTick 超时之前，该线程都会处于阻塞状;
			*   2, 而一旦超时或者收到了其他线程的通知，wait_for返回
			*	3, 当wait_for()或者wait()进入等待后，会调用此处的lock->unlock()方法, 意味着在wait_for等待条件变量时(此处是等待 realTick 时间)不会占用该锁
			*	4, 当wait_for()等待结束后会重新调用 lock->lock()方法, 然后作用域结束再调用 lock->unlock(), 目的是使得wait_for()仿佛没有接触过加锁和解锁,
			*/
			std::cv_status status = m_waitCond.wait_for(lock, realTick);

			// for print
			std::cout << __FUNCTION__ << "---->3 be called! thread id: " << std::this_thread::get_id() << " realTick[" << realTick.count() << "]" << std::endl;
		}
	}

	m_timers.clear();
}

void ThreadTimerClass::tick()
{
	// 获取当前的时间点
	std::chrono::time_point<std::chrono::steady_clock, std::chrono::milliseconds> curStart;
	curStart = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now());

	std::vector<TimerNode*> outTimers;

	// delete invalied timer, get timeout timer
	{
		// 1, 作用域内构造条件变量锁,调用lock->lock(), 作用域结束时自动析构调用lock->unlock();
		// 2, 只有(1)当作用域内的循环处理结束或者 (2)m_waitCond.notify_one() or m_waitCond.notify_all()被调用时, 该条件变量锁会得到释放;
		// 3, 此处用来保护 m_timers vector容器
		std::unique_lock<std::mutex> lock(m_waitConMutex);
		std::vector<TimerNode>::iterator it = m_timers.begin();
		while (it != m_timers.end())
		{
			if (it->m_deleteLater)
			{
				it = m_timers.erase(it);
			}
			else
			{
				if (curStart >= it->m_expire)
				{
					outTimers.push_back(&(*it));
				}
				it++;
			}
		}
	}

	// run out timer
	{
		// 1, 作用域内构造超时锁,调用lock->lock(), 作用域结束时自动析构调用lock->unlock();
		// 2, 此锁是为了保护 m_deleteLater ,间接锁了m_timers(outTimers里存放的是m_timers里的指针)
		// 3, 此锁动作将维持到开启定时器传入的函数执行结束.
		std::unique_lock<std::mutex> lock(m_outTimersMutex);
		for (auto& item : outTimers)
		{
			if (!item->m_deleteLater && item->m_cb)
			{
				item->m_cb(item->m_userData);
				item->m_expire = curStart + std::chrono::milliseconds(item->m_interval);
			}
		}
	}

	//
	std::chrono::time_point<std::chrono::steady_clock, std::chrono::milliseconds> curStop;
	curStop = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now());
	m_consume = curStop - curStart;

	{
		// 此锁将不会生效,自己线程里的io竞争
		std::unique_lock<std::mutex> lock(m_coutMutex);
		std::cout << __FUNCTION__ << " threadID[" << std::this_thread::get_id() << "] count[" << m_consume.count() << "] tick end!" << std::endl;
	}
}

