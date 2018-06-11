/*================================================================
*   Copyright (C) 2018 Renleilei. All rights reserved.
*   
*   文件名称：048_structArrayReplaceMap.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2018年05月05日
*   描    述：
*   版    本: Version 1.00
*   编译命令: g++ -o main 048_structArrayReplaceMap.cpp
================================================================*/

#include <iostream>
#include <map>

using namespace std;

struct mapReplace
{
	int			iGroupID;
	int			iCount;
};

void _print(struct mapReplace *pointer, int iSize);

int main()
{
	int iSize = 2;

	struct mapReplace _array[iSize];

	_print(_array, iSize);

	return 0;
}


void _print(struct mapReplace *pointer, int iSize)
{
	struct mapReplace *_array = pointer;
	_array[0].iGroupID = 1000;
	_array[0].iCount	 = 1;
	_array[1].iGroupID = 1100;
	_array[1].iCount	 = 2;

	for(int i = 0; i < iSize; i++)
	{
		cout<<_array[i].iGroupID<<" "<<_array[i].iCount<<endl;
	}
}
