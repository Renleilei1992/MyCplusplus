/*================================================================
*   Copyright (C) 2018 Renleilei. All rights reserved.
*   
*   文件名称：038_structArgv.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2018年03月18日
*   描    述：
*   版    本: Version 1.00
*   编译命令: g++ -o main 038_structArgv.cpp
================================================================*/

#include <iostream>

using namespace std;

struct Msg
{
	long phoneNum;
	int year;
	const char* msgContent;
};

void printMsg(int ID, Msg msgObj);
void printMsg_01(int ID, Msg *msgPointer);

int main()
{
	const char* content = "hello world";
	Msg msg1 = {18801951060, 2018, content};

	int msgID = 10;
	printMsg(msgID, msg1);
	cout<<"------------------"<<endl;
	printMsg_01(msgID, &msg1);

	return 0;
}

void printMsg(int ID, Msg msgObj)
{
	cout<<"ID: "<<ID<<endl;
	cout<<"phoneNum: "<<msgObj.phoneNum<<endl;
	cout<<"year: "<<msgObj.year<<endl;
	cout<<"MsgContent: "<<msgObj.msgContent<<endl;
}

void printMsg_01(int ID, Msg *msgPointer)
{
	if(msgPointer == NULL)
	{
		return;
	}
	cout<<"ID: "<<ID<<endl;
	cout<<"phoneNum: "<<msgPointer->phoneNum<<endl;
	cout<<"year: "<<msgPointer->year<<endl;
	cout<<"MsgContent: "<<msgPointer->msgContent<<endl;
}
