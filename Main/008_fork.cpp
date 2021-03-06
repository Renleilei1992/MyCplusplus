/*================================================================
*   Copyright (C) 2017 Renleilei. All rights reserved.
*   
*   文件名称：008_fork.cpp
*   创 建 者：Renleilei (renleilei@foxmail.com)
*   创建日期：2017年11月10日
*   描    述：
*   版    本: Version 1.00
*   编译方法: g++ -o main ./008_fork.cpp -O3 -g -Wall
================================================================*/


/* 测试循环fork的进程数量及pid号 */

#include <iostream>
#include <unistd.h>
#include <assert.h>

extern "C"

using namespace std;

void assert_test(int i_val);


int main(int argc,char **argv)
{
	pid_t pid_num = 0;
	int count = 0;

	for(int i = 1; i < 4; i++){
		pid_num = fork();
		if(pid_num < 0){
			cout<<"error in fork!"<<endl;
		}else if(pid_num == 0){
			cout<<"I'm the child process, my process id is ["<<getpid()<<"]"<<endl;
			assert_test(1);
			count++;
		}else{
			cout<<"I'm the father process, my process id is ["<<getpid()<<"]"<<endl;
			assert_test(3);
		}
		
	//	cout<<"第"<<i<<"次pid = ["<<pid_num<<"]"<<endl;
    //  cout<<"---------------------------"<<endl;
	//	sleep(1);
	}
	return 0;
}

void assert_test(int i_val){
	if(1 == i_val){
		i_val--;
		cout<<"it's time quit! :)"<<i_val<<endl;
		assert(i_val);
		return;
	}else{
		cout<<"it's an another opportunity to quit! :)"<<i_val%2<<endl;
		assert(i_val%2);
		return;
	}
}

