/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：097_ThreadLearning_Windows.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年03月14日
*   描    述：请注意此文件为windows平台的.cpp文件,请使用vs进行编译和调试
*   版    本: Version 1.00
================================================================*/

#include <iostream>
#include <stdio.h>
#include <process.h>
#include <windows.h>
#include <assert.h>

using namespace std;

DWORD WINAPI ThreadFunc_TestAssert(LPVOID);	// 声明一个线程需要执行的函数 结论：当子线程assert的时候，子线程会中断，主线程不会中断会继续执行，但是当点击弹出的窗口上的按钮时(中止、继续、忽略)，均会中断主线程

int main(int argc, char** argv)
{
	std::cout << "hello my windows!" << endl;
	//_sleep(1000);


	HANDLE hThread;
	DWORD  threadID;

	hThread = CreateThread(NULL, 0, ThreadFunc_TestAssert, 0, 0, &threadID);	// 创建线程
	//cout << "我是主线程, pid = " << GetCurrentThreadId() << endl;
	/*for (int i = 0; i < 50; i++) {
		_sleep(10);
		cout << "我是主线程， pid = " << GetCurrentThreadId() << " i = [" << i << "]" << endl;
	}*/

	int j = 0;
	while (1) {
		_sleep(10);
		cout << "我是主线程， pid = " << GetCurrentThreadId() << " i = [" << j << "]" << endl;
		j++;
	}

	_sleep(2000);

	//return 0;
}

DWORD WINAPI ThreadFunc_TestAssert(LPVOID p)
{
	_sleep(1000);
	cout << "我是子线程， pid = " << GetCurrentThreadId() << endl;
	for (int i = 0; i < 20; i++) {
		cout << "我是子线程， pid = " << GetCurrentThreadId() << " i = [" << i << "]" << endl;
		if (i == 10) {
			assert(0);		// 结论：当子线程assert的时候，子线程会中断，主线程不会中断会继续执行，但是当点击弹出的窗口上的按钮时(中止、继续、忽略)，均会中断主线程
		}
	}
	return 0;
}

/*
HANDLE WINAPI CreateThread(
_In_opt_  LPSECURITY_ATTRIBUTES  lpThreadAttributes,			// 第一个参数 lpThreadAttributes 表示线程内核对象的安全属性，一般传入NULL表示使用默认设置
_In_      SIZE_T                 dwStackSize,					// 第二个参数 dwStackSize 表示线程栈空间大小。传入0表示使用默认大小（1MB）
_In_      LPTHREAD_START_ROUTINE lpStartAddress,				// 第三个参数 lpStartAddress 表示新线程所执行的线程函数地址，多个线程可以使用同一个函数地址
_In_opt_  LPVOID                 lpParameter,					// 第四个参数 lpParameter 是传给线程函数的参数
_In_      DWORD                  dwCreationFlags,				// 第五个参数 dwCreationFlags 指定额外的标志来控制线程的创建，为0表示线程创建之后立即就可以进行调度，如果为CREATE_SUSPENDED则表示线程创建后暂停运行，这样它就无法调度，直到调用ResumeThread()
_Out_opt_ LPDWORD                lpThreadId						// 第六个参数 lpThreadId 将返回线程的ID号，传入NULL表示不需要返回该线程ID号
);

*/
