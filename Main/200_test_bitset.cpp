/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：200_test_bitset.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年10月21日
*   描    述：简单使用bitset, 并新增c++11的新特性使用
*   版    本: Version 1.00
================================================================*/

#include <iostream>
#include <bitset>

using namespace std;

void useBitset();

int main()
{
	useBitset();

	return 0;
}

void useBitset()
{
	cout << __func__ << " be called! " << endl;

	bitset<16> bt1;		// 构造16位的bt1, 每一位的值都是0
	cout << "bt1: " << bt1.to_string() << endl;

	bitset<70> bt2(0x123456789ABCDEF);		// 使用unsigned long long 构造70位的bt2
	cout << "bt2: " << bt2.to_string() << " " << bt2 << endl;

	string str1("01010011");
	bitset<8> bt3(str1, 2, 4);		// 从字符串构造, 使用字符串第2个字符开始的4位
	cout << "bt3: " << bt3.to_string() << endl;

	string str2("ABABBAA");
	bitset<8> bt4(str2, 0, 8, 'A', 'B');	// 从字符串构造, 使用第0个字符开始的8位, 将'A'转换为0, 将'B'转换为1
	cout << "bt4: " << bt4.to_string() << endl;

	// 信息取得
	bitset<4> t1(0x02);
	bitset<6> t2(0x3f);
	bitset<8> t3(0x00);
	cout << "t1: " << t1.to_string() << " t2: " << t2.to_string() << " t3: " << t3.to_string() << endl; 

	// 测试是否存在1
	cout << "any?? " << t1.any() << " " << t2.any() << " " << t3.any() << endl;
	// 测试是否都是1
	cout << "all?? " << t1.all() << " " << t2.all() << " " << t3.all() << endl;
	// 测试是否没有1
	cout << "none?? " << t1.none() << " " << t2.none() << " " << t3.none() << endl;
	// 取得bitset的长度
	cout << "size: " << t1.size() << " " << t2.size() << " " << t3.size() << endl;
	// 使用两种形式取得指定位的状态
	cout << "t1[1][0]=" << t1.test(1) << ", " << t1[0] << endl;
}
