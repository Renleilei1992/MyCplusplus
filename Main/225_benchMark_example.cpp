/*================================================================
*   Copyright (C) 2020 Renleilei. All rights reserved.
*   
*   文件名称：225_benchMark_example.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2020年01月01日
*   描    述：
*   版    本: Version 1.00
*   参考链接: https://www.zhihu.com/question/359420368/answer/923702907
================================================================*/

#include <chrono>
#include <iostream>
#include <vector>
using namespace std;
using namespace std::chrono;

#define BENCHMARK_BEGIN \
  {                     \
    auto time_before = high_resolution_clock::now();

#define BENCHMARK_END(description)                                            \
  auto time_now = high_resolution_clock::now();                               \
  auto time_us = duration_cast<microseconds>(time_now - time_before).count(); \
  cout << description << ": " << time_us << " us" << std::endl;               \
  }

int main()
{
	cout << "---------- begin benchmark -----------" << endl;
	constexpr size_t N = 1000000;
	vector<int> _vec01;
	_vec01.reserve(N);

	BENCHMARK_BEGIN
	for(size_t i = 0; i < N; i++) {
		_vec01.emplace_back(static_cast<int>(i));
	}
	BENCHMARK_END("1.vector")
	
	return 0;
}
