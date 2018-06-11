/*================================================================
*   Copyright (C) 2018 Renleilei. All rights reserved.
*   
*   文件名称：055_vectorResizeReserve.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2018年05月29日
*   描    述：
*   版    本: Version 1.00
*   编译命令: 
================================================================*/

#include <iostream>
#include <vector>


using namespace std;

int main(int argc, char **argv)
{
	std::vector<int> vec_01 = {1, 2, 3, 4, 5};

	for(auto ivec : vec_01){cout << ivec << endl;}

	return 0;
}
