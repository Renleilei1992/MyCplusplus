/*================================================================
*   Copyright (C) 2020 Renleilei. All rights reserved.
*   
*   文件名称：231_0x_validate.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2020年05月12日
*   描    述：
*   版    本: Version 1.00
================================================================*/

#include <iostream>
using namespace std;

enum EValue {
	E_1 = 0x0001,
	E_2 = 0x0002,
	E_3 = 0x0003,
	E_4 = 0x0004,

	E_15 = 0x000F,
};

int main()
{
	cout << "E_1:" << E_1 << endl;
	cout << "E_2:" << E_2 << endl;
	cout << "E_3:" << E_3 << endl;
	cout << "E_4:" << E_4 << endl;
	cout << "E_15:" << E_15 << endl;


	cout << "E_1 | E_4: " << (E_1 | E_4) << endl;	// 5      0001 | 0100 = 0101
	cout << "E_3 | E_4: " << (E_3 | E_4) << endl;   // 7  00000011 | 0100 = 0111 = 1*2^2 + 1*2^1 + 1*2^0 = 7
	cout << "E_3 | E_15: " << (E_3 | E_15) << endl; // 15 00001111 | 0011 = 1111 = 1*2^3 + 1*2^2 + 1*2^1 + 1*2^0 = 15

	cout << "E_3 & 0x0010: " << (E_3 & 0x0010) << endl;
	return 0;
}
