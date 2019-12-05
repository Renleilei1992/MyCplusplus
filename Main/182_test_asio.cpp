/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：182_test_asio.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年08月27日
*   描    述：
*   版    本: Version 1.00
*   编译指令: g++ -std=c++11 -DASIO_STANDALONE -pthread -o main 182_test_asio.cpp -I../include/asio/include/asio  // 目前已能编译通过 
*   编译步骤: g++ -std=c++11 -DASIO_STANDALONE -pthread -o main 182_test_asio.cpp  // 在ubuntu安装了 asio 开发库之后 sudo apt-get install -y libasio-dev
================================================================*/

//#define ASIO_STANDALONE
#define ASIO_HAS_STD_ADDRESSOF
#define ASIO_HAS_STD_ARRAY
#define ASIO_HAS_CSTDINT
#define ASIO_HAS_STD_SHARED_PTR
#define ASIO_HAS_STD_TYPE_TRAITS

#include <iostream>
#include <string>
#include <memory>
#include <asio.hpp>

using namespace std;

int main()
{
	asio::io_service myIOService;

	return 0;
}
