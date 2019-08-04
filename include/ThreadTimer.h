#ifndef _THREAD_TIMER__H_
#define _THREAD_TIMER__H_

#include <chrono>
#include <functional>
#include <mutex>
#include <atomic>
#include <thread>
#include <assert.h>
#include <vector>

namespace BYTEVIEW_COMMON {

	/*		
	// 线程定时器 example
	ThreadTimer ttm;

	std::cout << "start thread \n" << std::endl;
	ttm.startThread(400);

	// test delay timer
	std::cout << "start delay timer 5 2 \n" << std::endl;
	int timer1 = ttm.startTimer(5000, 2000, [](void*) {
		std::cout << "delay timer 5 2 \n" << std::endl;
		
	});

	// test normal timer
	std::cout << "start normal timer 0 1 \n" << std::endl;
	int timer2 = ttm.startTimer(0, 1000, [](void*) {
		std::cout << "normal timer 0 1 \n" << std::endl;
	});		

	std::this_thread::sleep_for(std::chrono::seconds(20));
	
	
	ttm.stopTimer(timer1);
	std::cout << "stop delay timer 5 2 \n" << std::endl;

	std::this_thread::sleep_for(std::chrono::seconds(5));
	
	ttm.stopTimer(timer2);
	std::cout << "stop normal timer 0 1 \n" << std::endl;
	
	ttm.stopThread();
	std::cout << "stop thread \n" << std::endl;
	
	std::cout << "success \n" << std::endl;
	*/

	/**
	 *@brief 单线程定时器，支持多定时器
	 *		 定时器不可做耗时任务
	 */
	class ThreadTimer
	{
	public:
		ThreadTimer() {}
		~ThreadTimer() {}

		/**
		* @brief 启动定时器线程
		* @param [in] tict 单位ms
		*         定时触发周期，决定定时器最小精度
		*/
		void startThread(int tick)
		{
			if (m_timerThread)
			{
				return;
			}
			if (tick <= 0)
			{
				tick = 500;
			}
			m_tick = std::chrono::milliseconds(tick);
			m_timerThread = new std::thread(&ThreadTimer::threadProc, this);
		}

		/**
		* @brief 停止定时器线程(不能在定时器回调中调用)
		*/
		void stopThread()
		{
			if (!m_timerThread)
			{
				return;
			}			

			m_quitFlag = true;

			{
				std::unique_lock<std::mutex> lock(m_waitCondMutex);
				m_waitCond.notify_one();
			}

			m_timerThread->join();
			delete m_timerThread;
			m_timerThread = nullptr;
		}

		/**
		* @brief 启动定时器
		* @param [in] delay
		*         延时启动时间，单位ms
		* @param [in] interval
		*         定时器触发间隔，单位ms
		* @param [in] cb
		*         定时器回调函数
		* @param [in] params
		*         定时器回调函数参数
		* @return
		*        -1: 失败
		*     other: 定时器id
		*/
		int startTimer(int delay, int interval, std::function<void(void*)> cb, void* params = nullptr)
		{
			if (!m_timerThread || delay < 0 || interval <= 0 || !cb)
			{
				return -1;
			}
			std::unique_lock<std::mutex> lock(m_waitCondMutex);
			int timerID = m_timerID++;			
			if (m_timerID >= 999999)
			{
				assert(0);
				return -1;
			}
			TimerNode node(timerID, delay, interval, cb, params);

			m_timers.push_back(node);
			return timerID;
		}

		/**
		* @brief 停止定时器
		* @param [in] id
		*         定时器id
		*/
		void stopTimer(int id)
		{
			if (!m_timerThread || id < 0 || id > 999999)
			{
				return;
			}			
			if (std::this_thread::get_id() == m_timerThread->get_id())
			{
				std::unique_lock<std::mutex> lock(m_waitCondMutex);
				std::vector<TimerNode>::iterator it = m_timers.begin();
				for (; it != m_timers.end(); it++)
				{
					if (it->m_id == id)
					{
						it->m_deleteLater = true;
						break;
					}
				}
			}
			else
			{
				std::unique_lock<std::mutex> lock(m_waitCondMutex);
				std::unique_lock<std::mutex> lockOut(m_outTimersMutex);
				std::vector<TimerNode>::iterator it = m_timers.begin();
				for (; it != m_timers.end(); it++)
				{
					if (it->m_id == id)
					{
						it->m_deleteLater = true;
						break;
					}
				}
			}			
		}

	protected:
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
			std::chrono::time_point<std::chrono::steady_clock, std::chrono::milliseconds> m_expire;
			int m_interval;
			int m_id;
			std::function<void(void*)> m_cb = nullptr;
			void* m_userData = nullptr;
			bool m_deleteLater = false;
		};

		void threadProc()
		{
			while (!m_quitFlag)
			{
				tick();
				{
					std::unique_lock<std::mutex> lock(m_waitCondMutex);
					std::chrono::milliseconds realTick = m_tick - m_consume;
					std::cv_status status = m_waitCond.wait_for(lock, realTick);
				}
				
			}
			m_timers.clear();
		}

	private:
		void tick()
		{
			std::chrono::time_point<std::chrono::steady_clock, std::chrono::milliseconds> curStart;
			curStart = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now());
			
			std::vector<TimerNode*> outTimers;
			// delete invaild timer, get timeout timer
			{
				std::unique_lock<std::mutex> lock(m_waitCondMutex);				
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

			std::chrono::time_point<std::chrono::steady_clock, std::chrono::milliseconds> curStop;
			curStop = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now());
			m_consume = curStop - curStart;
		}

	private:
		std::vector<TimerNode> m_timers;
		std::mutex m_outTimersMutex;
		std::mutex m_waitCondMutex;
		std::condition_variable m_waitCond;
		std::atomic<bool> m_quitFlag = { false };
		std::thread* m_timerThread = nullptr;
		std::chrono::milliseconds m_tick;
		std::chrono::milliseconds m_consume = std::chrono::milliseconds(0);
		int m_timerID = 0;
	};	

} // namespace BYTEVIEW_COMMON

#endif //_THREAD_TIMER__H_