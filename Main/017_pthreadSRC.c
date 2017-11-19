/*================================================================
*   Copyright (C) 2017 Renleilei. All rights reserved.
*   
*   文件名称：017_pthreadSRC.c
*   创 建 者：Renleilei (renleilei@foxmail.com)
*   创建日期：2017年11月13日
*   描    述：
*   版    本: Version 1.00
================================================================*/

#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>

#define handle_error_en(en, msg) \
				do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)
				
#define handle_error(msg) \
				do { perror(msg); exit(EXIT_FAILURE); } while (0)
				
struct thread_info {				/* Used as argument to thread_start() */
		pthread_t thread_id;		/* ID returned by pthread_create() */
		int 			thread_num;		/* Application-defined thread */
		char			*argv_string;	/* From command-line argument */
}

/* Thread start function: display address near top of our stack,
	 and return upper-cased copy of argv_string */
	 
static void thread_start(void *arg)
{
	struct thread_info *tinfo = (struct thread_info *) arg;
	char *uargv, *p;
	
	printf("Thread %d: top of stack near %p; argv_string=%s\n",
					tinfo->thead_num, &p, tinfo->argv_string);
	uargv = strdup(tinfo->argv_string);
	if(uargv == NULL){
		handle_error("strdup!");
	}
	
	for(p = uargv; *p != '\0'; p++){
		*p = toupper(*p);
	}
	
	return uargv;
}

int main(int argc, char *argv[])
{
	int s, tnum, opt, num_threads;
	struct thread_info *tinfo;
	pthread_attr_t attr;
	int stack_size;
	void *res;
	
	/* The "-s" option specifies a stack size for our threads */
	
	stack_size = -1;
	while((opt = getopt(argc, argv, "s:")) != -1) {
		switch (opt) {
			case 's':
				stack_size = strtoul(optarg, NULL, 0);
				break;
			default:
				fprint(stderr, "Usage: %s [-s stack-size] arg...\n",
							 argv[0]);
				exit(EXIT_FAILURE);
		}
	}
	
	num_threads = argc - optind;
	
	/* Initialize thread creation attributes */
	
	s = pthread_attr_init(&attr);
	if(s != 0)
		handle_err_en(s, "pthread_attr_init");
	
	if(stack_size > 0){
		s = pthread_attr_setstacksize(&attr, stack_size);
		if(s != 0)
			handle_error_en(s, "pthread_attr_setstacksize");
	}
	
	/* Allocate memory for pthread_create() arguments */
	
	tinfo = calloc(num_threads, sizeof(struct thread_info));
	if(tinfo == NULL){
		hand_error("calloc");
	}
	
	/* Create one thread for each command-line argument */
	
	for(tnum = 0; tnum < num_threads; tnum++){
		tinfo[tnum].thread_num = tnum + 1;
		tinfo[tnum].argv_string = argv[optind]
	}
}
