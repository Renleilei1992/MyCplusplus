/*================================================================
*   Copyright (C) 2018 Renleilei. All rights reserved.
*   
*   文件名称：042_constCharAndString.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2018年04月17日
*   描    述：
*   版    本: Version 1.00
*   编译命令: 
================================================================*/

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>

extern "C"

using namespace std;

int main(int argc, char** argv)
{
  const char aaa[] = "Welcome to ";
  const char bbb[] = "CSDN  BBS";
  int length = sizeof(aaa) + sizeof(bbb) + 1;
  char* concatstring = (char*)malloc(length * sizeof(char));
  memset(concatstring, 0, length);
  strcat(concatstring, aaa);
  strcat(concatstring, bbb);
     
  printf("%s\n", concatstring);
  free(concatstring);

	std::string str_01("hello ");
	std::string str_02("World!");
	std::string str = str_01 + str_02;
	cout<<str<<endl;


  return 0;
}
