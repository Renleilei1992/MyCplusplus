/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：177_test_to_string.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年08月22日
*   描    述：使用c++11的 std::to_string 方法将数字转为字符串
*   版    本: Version 1.00
================================================================*/

#include <iostream>

using namespace std;

int main()
{
	double f1 = 23.43;
	double f2 = 1e-9;
	double f3 = 1e40;
	double f4 = 1e-40;
	double f5 = 123456789;

	std::string f1_str = std::to_string(f1);	// 23.430000
	std::string f2_str = std::to_string(f2);	// 0.000000
	std::string f3_str = std::to_string(f3);	// 10000000000000000303786028427003666890752.000000
	std::string f4_str = std::to_string(f4);	// 0.000000
	std::string f5_str = std::to_string(f5);	// 123456789.000000

	cout << "f1: " << f1 << " f1_str: " << f1_str << "\n"
		 << "f2: " << f2 << " f2_str: " << f2_str << "\n"
		 << "f3: " << f3 << " f3_str: " << f3_str << "\n"
		 << "f4: " << f4 << " f4_str: " << f4_str << "\n"
		 << "f5: " << f5 << " f5_str: " << f5_str << "\n";
	return 0;
}
