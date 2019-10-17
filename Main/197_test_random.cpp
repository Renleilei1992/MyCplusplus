/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：197_test_random.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年09月11日
*   描    述：简单测试C++11引入的标准random随机数库
*   版    本: Version 1.00
*   参考文献: https://zh.cppreference.com/w/cpp/header/random (多种模板及随机方式)
================================================================*/

#include <iostream>
#include <random>		// std::uniform_int_distribution ...
#include <cstdlib>		// rand() & srand() 不推荐
#include <ctime>		// time()

using namespace std;

void testOldStyleRandom();	// 测试古老的随机数使用方式
void testRandomEngine();	// 测试新的随机数引擎
void testNewStyleRandom();	// 测试C++11的随机数使用方式
void testRandomFunc01();

int main()
{
	testOldStyleRandom();
	testRandomEngine();
	testRandomFunc01();
	return 0;
}

void testOldStyleRandom()
{
	cout << __func__ << " be called! random number below: " << endl;
	int a = rand();		// 在RAND_MAX范围内的随机数
	cout << "old style random number: [" << a << "]" << endl;			// 1804289383
	
	// 重新使用时间作为随机数种子
	srand((unsigned)time(nullptr));
	int b = rand();
	cout << "old style random number: [" << b << "]" << endl;
	int c = rand() % 10;
	cout << "old style random number between 0 ~ 9: [" << c << "]" << endl;
}

void testRandomEngine()
{
	// 会观察到引擎生成的10个随机数在多次执行的情况下是同一批
	cout << __func__ << " be called! random number below: " << endl;
	std::default_random_engine eng;
	cout << "随机数引擎 最小值: " << eng.min() << endl;
	cout << "随机数引擎 最大值: " << eng.max() << endl;
	for (int i = 0; i < 10; ++i) {
		cout << "随机数引擎(无种子): " << i << ": " << eng() << endl;
	}

	// https://zh.cppreference.com/w/cpp/numeric/random 推荐用法
	std::random_device r;	// 以随机值播种[使用硬件熵源的非确定随机数生成器]
	// 选择 1~6 之间的随机数
	std::default_random_engine e1(r());
	std::uniform_int_distribution<int> uniform_dist(1, 6);
	int mean = uniform_dist(e1);
	std::cout << "随机数引擎根据硬件熵种子得到的1~6之间的随机数: " << mean << endl;

	// 使用种子后的10个随机数
	for (int i = 0; i < 10; ++i) {
		cout << "随机数引擎(有种子): " << i << ": " << e1() << endl;
	}
}

void testNewStyleRandom()
{
	cout << __func__ << " be called! random number below: " << endl;
	
}

void testRandomFunc01()
{
	cout << __func__ << " be called! random number below: " << endl;
	// 初始化随机数种子
	std::mt19937 mt;
	mt.seed(std::random_device()());

	// 创建一个均匀分布
	std::uniform_int_distribution<std::mt19937::result_type> dist1(1, 999);
	cout << "1~999 range uniform random result: [" << dist1(mt) << "]" << endl;

	// 简单写法
	std::uniform_int_distribution<int> dist2(1, 10000);
	cout << "1~10000 range uniform random result: [" << dist2(mt) << "]" << endl;

	// 均匀分布, 随机生成在一定范围的小数
	std::uniform_real_distribution<double> dist3(-1, 1);
	cout << "-1~1 range uniform random result: [" << dist3(mt) << "]" << endl;
}
