/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：152_chrono.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年08月04日
*   描    述：
*   版    本: Version 1.00
*	编译指令: g++ -o main 152_chrono.cpp -std=c++11	
================================================================*/

#include <chrono>
#include <iostream>
#include <ctime>
#include <sys/time.h>
#include <cstdint>

using namespace std;
using namespace chrono;

int main()
{
	std::chrono::time_point<std::chrono::system_clock> p1, p2, p3;

	auto startVal = system_clock::now();

	auto endVal = system_clock::now();

	auto durationVal = duration_cast<microseconds>(endVal - startVal);

	std::time_t tt, tt1, tt2;
	tt = system_clock::to_time_t(startVal);
	std::cout << "start: " << ctime(&tt) << std::endl;
	tt1 = system_clock::to_time_t(endVal);
	std::cout << "end  : " << ctime(&tt1) << std::endl;
	double num = durationVal.count();
	std::cout << "num: " << num << std::endl;
	std::cout << "period::num: " << microseconds::period::num << std::endl;
	std::cout << "period::den: " << microseconds::period::den << std::endl;
//	std::cout << "cost : " << double(durationVal.count()) * microseconds::period::num / microseconds::period::den << " seconds" << std::endl;

	int tick = 500;
//	std::chrono::milliseconds m_tick = std::chrono::milliseconds(tick);
//	cout << "m_tick: " << m_tick << endl;

	typedef duration<int,std::ratio<60*60*24>> days_type;
	time_point<system_clock,days_type> today = time_point_cast<days_type>(system_clock::now());
	std::cout << today.time_since_epoch().count() << " days since epoch" << std::endl;

	std::chrono::steady_clock::time_point t1 = std::chrono::system_clock::now();
	std::cout << "Hello World\n";
	std::chrono::steady_clock::time_point t2 = std::chrono::system_clock::now();
//std::cout << (t2-t1).count()<<” tick count”<<endl;

	return 0;
}
