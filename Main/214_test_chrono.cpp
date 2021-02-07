/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：214_test_chrono.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年11月18日
*   描    述：简略测试C++11引入的chrono时间
*   版    本: Version 1.00
*   编译指令: g++ -o main 214_test_chrono.cpp -std=c++14 -lpthread
================================================================*/


/*
Hello, plz wait..
Waited: 2000.09 ms
*/

#include <iostream>
#include <chrono>
#include <thread>
#include <ctime>

using namespace std;

void showDurationTime();
void showDetailTime();

int main()
{

	showDetailTime();

	showDurationTime();
	return 0;
}

void showDurationTime()
{
	using namespace std::chrono_literals;	// c++14
	cout << "Hello, plz wait.." << endl;

	// 类型: high_resolution_clock::time_point
	auto start = std::chrono::high_resolution_clock::now();				//拥有最短可用计次周期的时间
	std::this_thread::sleep_for(2s);		// c++14	(注意此处的2s或者200ms都是需要 c++14的std::chrono_literals 支持)
	auto end = std::chrono::high_resolution_clock::now();

	// std::chrono::duration<double, std::ratio<1, 1000>>
	std::chrono::duration<double, std::milli> elapsed = end - start;

	cout << "Waited 1: " << elapsed.count() << " ms\n";

	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(end -start);
	cout << "Waited 2: " << time_span.count() << " s\n";

	// time point
	std::time_t tt = std::chrono::high_resolution_clock::to_time_t(start);
	cout << "time point start: " << start.time_since_epoch().count() << " time: " << ctime(&tt) << endl;

}

void showDetailTime()
{
	using namespace std::chrono;
	using std::chrono::system_clock;

	// 1, now() 		是当前时间 time_point
	// 2, to_time_t()	time_point转换为time_t秒
	// 3, from_time_t() 从time_t转换为time_point
	std::chrono::duration<int, std::ratio<60*60*24>> one_day(1);

	system_clock::time_point today = system_clock::now();
	system_clock::time_point tomorrow = today + one_day;

	std::time_t tt;
	tt = system_clock::to_time_t(today);
	cout << __func__ << "::  this year is: " << (localtime(&tt)->tm_year + 1900)  <<  endl;
	cout << __func__ << ":: today is: " << ctime(&tt) << " this year is: " << (localtime(&tt)->tm_year + 1900) << " this hour is: " << (localtime(&tt)->tm_hour) <<  endl;

	tt = system_clock::to_time_t(tomorrow);
	cout << __func__ << ":: tomorrow will be: " << ctime(&tt) << endl;
}

/*
// 获取系统当前时间
std::string getCurrentSystemTime()
{
	auto tt = std::chrono::system_clock::to_time_t
		(std::chrono::system_clock::now());
	struct tm* ptm = localtime(&tt);
	char date[60] = { 0 };
	sprintf(date, "%d-%02d-%02d-%02d.%02d.%02d",
		(int)ptm->tm_year + 1900, (int)ptm->tm_mon + 1, (int)ptm->tm_mday,
		(int)ptm->tm_hour, (int)ptm->tm_min, (int)ptm->tm_sec);
	return std::string(date);
}
*/

/*
	//std::chrono::system_clock::time_point today = std::chrono::system_clock::now();
	//std::time_t tt = std::chrono::system_clock::to_time_t(today);
	//int currentHour = localtime(&tt)->tm_hour;
	//if (currentHour < 8 || currentHour > 21) {
*/
