/*================================================================
*   Copyright (C) 2020 Renleilei. All rights reserved.
*   
*   文件名称：hello.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2020年04月03日
*   描    述：
*   版    本: Version 1.00
================================================================*/

#include <iostream>

using namespace std;

int main()
{
#ifdef _OPEN
	cout << "open!" << endl;
#else
	cout << "not open!" << endl;
#endif

}
