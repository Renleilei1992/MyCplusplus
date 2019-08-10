#pragma once
#ifndef _THREAD_TIMER_CLASS_H_
#define _THREAD_TIMER_CLASS_H_

#include <thread>			// std::thread
#include <chrono>
#include <functional>
#include <atomic>
#include <vector>
#include <mutex>			// std::mutex, std::unique_lock, std::condition_variable
#include <assert.h>
#include <condition_variable>

class ThreadTimerClass
{
public:
	ThreadTimerClass() {}
	~ThreadTimerClass() {}

	/**
	* @brief 启动定时器线程
	* @param [in] tick 单位ms
	*			定时触发周期，决定定时器的最小精度
	*/
	void startThread(int tick);

	/**
	* @brief 停止定时器线程(不能在定时器回调函数中使用)
	*/
	void stopThread();

	/**
	* @brief 启动定时器
	* @param [in] delay
	*			延时启动时间，单位ms
	* @param [in] interval
	*			定时器触发间隔，单位毫秒
	* @param [in] cb
	*			定时器回调函数
	* @param [in] params
	*			定时器回调函数参数
	* @return
	*			-1: 启动定时器失败
	*		 other: 定时器id
	*/
	int startTimer(int delay, int interval, std::function<void(void *)> cb, void *params = nullptr);

	/**
	* @brief 停止定时器(指定id)
	* @param [in] id
	*			定时器id
	*/
	void stopTimer(int id);

protected:
	/**
	* @brief 
	*/
	class TimerNode
	{
	public:
		TimerNode(int id, int delay, int interval, std::function<void(void*)> cb, void* params = nullptr)
			: m_cb(cb)
			, m_userData(params)
			, m_interval(interval)
			, m_id(id)
		{
			if (delay == 0)
			{
				m_expire = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() + std::chrono::milliseconds(interval));
			}
			else
			{
				m_expire = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() + std::chrono::milliseconds(delay));
			}
		}

	public:
		std::chrono::time_point<std::chrono::steady_clock, std::chrono::milliseconds> m_expire;		// 过期时间: 当delay为0时,该值为一个间隔时间;当delay不为0时,该值为延时delay
		int m_interval = 0;
		int m_id = 0;
		std::function<void(void*)> m_cb = nullptr;
		void* m_userData = nullptr;
		bool m_deleteLater = false;
	};

	/**
	* @brief 线程回调函数
	*/
	void threadProc();

private:
	/**
	* @brief
	*/
	void tick();

private:
	std::thread*				m_timerThread = nullptr;
	std::chrono::milliseconds	m_tick = std::chrono::milliseconds(0);
	std::chrono::milliseconds	m_consume = std::chrono::milliseconds(0);
	std::atomic<bool>			m_bQuitFlag = { false };						// std::atomic<T>模板类可以使对象操作为原子操作，避免多线程竞争问题

	std::vector<TimerNode>		m_timers;
	std::mutex					m_waitConMutex;					// 锁1, 条件变量的锁, 配合m_waitCond(条件变量)使用
	std::mutex					m_outTimersMutex;				// 锁2, 超时锁,
	std::mutex					m_coutMutex;					// 锁3, io锁,
	std::condition_variable		m_waitCond;						// 条件变量配合锁

	int							m_timerID = 0;
};

#endif // _THREAD_TIMER_CLASS_H_


