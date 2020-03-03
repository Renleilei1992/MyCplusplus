/*================================================================
*   Copyright (C) 2020 Renleilei. All rights reserved.
*   
*   文件名称：227_getMd5.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2020年03月03日
*   描    述：简单写一个可以获取文件MD5值的C++代码(Linux)
*   版    本: Version 1.00
*   编译指令: g++ -o main 227_getMd5.cpp -std=c++11 -l crypto
================================================================*/

#include <fstream>
#include <openssl/md5.h>
#include <string.h>
#include <iostream>

using namespace std;

int getFileMd5(const std::string &fileFullPath, std::string &md5Val);

int main()
{
	std::string md5RetVal = "";
	
	int ret = getFileMd5(std::string("/usr/Johnny/asio.tar"), md5RetVal);

	if (ret != 0) {
		std::cout << "file error!" << endl;
	}
	return 0;
}

int getFileMd5(const std::string &fileFullPath, std::string &md5Val)
{
	md5Val.clear();

	std::ifstream file(fileFullPath.c_str(), std::ifstream::binary);
	if (!file)
		return -1;

	MD5_CTX md5Context;
	MD5_Init(&md5Context);

	char buff[1024 * 16];
	while(file.good()) {
		file.read(buff, sizeof(buff));
		MD5_Update(&md5Context, buff, file.gcount());
	}

	unsigned char result[MD5_DIGEST_LENGTH];
	MD5_Final(result, &md5Context);

	char hex[35];
	memset(hex, 0, sizeof(hex));
	for (int i = 0; i < MD5_DIGEST_LENGTH; ++i) {
		sprintf(hex + i * 2, "%02x", result[i]);
	}

	hex[32] = '\0';
	md5Val = string(hex);

	std::cout << "fileName: " << fileFullPath << "md5: " << md5Val << endl;

	return 0;
}
