/*================================================================
*   Copyright (C) 2017 Renleilei. All rights reserved.
*   
*   文件名称：016_pthread.cpp
*   创 建 者：Renleilei (renleilei@foxmail.com)
*   创建日期：2017年11月10日
*   描    述：
*   版    本: Version 1.00
*   编译方法: gcc -o main 016_pthread.cpp -O3 -lpthread -g -Wall
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
//#include <iostream>
#include <unistd.h>

//using namespace std;

//extern "C"

#define RETURN_MSG "Thank you!"
char msg[] = "Hello World!";
//string msg = "Hello World!";

void *thread_function(void *arg);
char *return_msg = "Thank you for the CPU time to handle this pthread!";

int main()
{
	int res;
	pthread_t a_thread;
	void *thread_result;
	
	res = pthread_create(&a_thread, NULL, thread_function, (void *)msg);
	if(res != 0){
		perror("Thread creation failed!");
		exit(EXIT_FAILURE);
	}
	printf("\n\n Creation success! waiting for a thread to finish...\n\n\n");
	res = pthread_join(a_thread, &thread_result);
	if(res != 0){
		perror("Thread join failed!");
		exit(EXIT_FAILURE);
	}
	printf("Thread joined, it returned: %s\n", (char *)thread_result);

	sleep(3);
	printf("[Main-Pthread] Message is modified: %s\n\n", msg);

	return EXIT_SUCCESS;
}

void *thread_function(void *arg)
{
	printf("[Child-Pthread] thread_function is running.. Argument is: %s\n", (char *)arg);
	sleep(1);
	printf("|-----|-----|-----|-----|-----|\n");
	sleep(1);
	printf("|---");
	sleep(3);
	printf("--------------------------|\n");
	sleep(1);
	strcpy(msg, "BYE!");
//	pthread_exit((void *)return_msg);
	pthread_exit((void *)RETURN_MSG);
}

/*
#include <pthread.h>
int pthread_create(pthread_t *thread, const pthread_attr_t *attr,void *(*start_routine) (void *), void *arg);
*/
