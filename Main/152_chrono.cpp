/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：152_chrono.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年08月04日
*   描    述：
*   版    本: Version 1.00
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

	auto durationVal = duration_cast<microseconds>(endVal -startVal);

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


	return 0;
}
