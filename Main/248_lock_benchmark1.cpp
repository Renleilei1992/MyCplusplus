/*================================================================
*   Copyright (C) 2020 Renleilei. All rights reserved.
*   
*   文件名称：248_lock_benchmark1.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2020年12月13日
*   描    述：
*   编译指令: g++ -o main 248_lock_benchmark1.cpp -std=c++11 -lpthread -fpermissive
*   版    本: Version 1.00
================================================================*/


#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <time.h>

// 创建的最大线程数
#define MAX_THD_SIZE 20


#define LOCK		// pthread_mutex_t, 互斥锁
//#define ATOMIC	// __sync_add_and_fetch, GCC自带的原子锁
//#define NOLOCK	// nolock, 无锁方式

// 启用自旋锁
//#define USE_SPINLOCK	// 将pthread_mutex_t 换为 pthread_spinlock_t 实现使用spinlock自旋锁方式

uint64_t max = 0;
uint64_t sum = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_spinlock_t spinlock;

// 使用互斥或者自旋锁方式自增
static void *incrment_with_lock (int *data)
{
        uint64_t i = 0;
        uint64_t count = max / MAX_THD_SIZE;
        for (; i < count; i++)
        {
#ifdef USE_SPINLOCK
				pthread_spin_lock (&spinlock);
                (*data)++;
                pthread_spin_unlock (&spinlock);
#else
                pthread_mutex_lock (&lock);
                (*data)++;
                pthread_mutex_unlock (&lock);
#endif
        }
}

// 使用无锁方式自增
static void *incrment_with_nolock (int *data)
{
        uint64_t i = 0;
        uint64_t count = max / MAX_THD_SIZE;
        for (; i < count; i++)
        {
                (*data)++;
        }
}

// 使用GCC自带的原子锁方式自增.
static void *incrment_with_atomic (int *data)
{
        uint64_t i = 0;
        uint64_t count = max / MAX_THD_SIZE;
        for (; i < count; i++)
        {
                __sync_add_and_fetch (data, 1);
        }
}

/*
bool is_digit (const char *s)
{
        if (s == NULL)
        {
                return false;
        }
        while (*s != '\0')
        {
                if (is_digit (*(s++)) == 0)
                {
                        return false;
                }
        }
        return true;
}
*/

int main (int argc, char *argv[])
{
        if (argc != 2 /*|| !is_digit (argv[1])*/)
        {
                fprintf (stdout, "usage: %s number \n", argv[0]);
                return 0;
        }

#ifdef USE_SPINLOCK
		// 自旋锁初始化
		pthread_spin_init(&spinlock, 0);
#else
		// 互斥锁初始化
		pthread_mutex_init(&lock, NULL);
#endif

        max = atoi (argv[1]);
        clock_t start, end;
        start = clock ();
        pthread_t thd[MAX_THD_SIZE];
        uint32_t i = 0;

#ifdef LOCK
        for (; i < MAX_THD_SIZE; i++)
        {
                pthread_create (&thd[i], NULL, incrment_with_lock, (void *) &sum);
        }
        for (i = 0; i < MAX_THD_SIZE; i++)
        {
                pthread_join (thd[i], NULL);
        }
        end = clock ();
#ifdef USE_SPINLOCK
        fprintf (stdout, "sum = %d,incremnt_with_spinlock run time :%f s\n", sum, (double) (end - start) / CLOCKS_PER_SEC);
#else
        fprintf (stdout, "sum = %d,incremnt_with_lock run time :%f s\n", sum, (double) (end - start) / CLOCKS_PER_SEC);
#endif
#endif

#ifdef ATOMIC
        for (; i < MAX_THD_SIZE; i++)
        {
                pthread_create (&thd[i], NULL, incrment_with_atomic, (void *) &sum);
        }
        for (i = 0; i < MAX_THD_SIZE; i++)
        {
                pthread_join (thd[i], NULL);
        }
        end = clock ();
        fprintf (stdout, "sum = %d,incremnt_with_atomic run time :%f s\n", sum, (double) (end - start) / CLOCKS_PER_SEC);
#endif

#ifdef NOLOCK
        for (; i < MAX_THD_SIZE; i++)
        {
                pthread_create (&thd[i], NULL, incrment_with_nolock, (void *) &sum);
        }
        for (i = 0; i < MAX_THD_SIZE; i++)
        {
                pthread_join (thd[i], NULL);
        }
        end = clock ();
        fprintf (stdout, "sum = %d,incremnt_with_nolock run time :%f s\n", sum, (double) (end - start) / CLOCKS_PER_SEC);
#endif
        return 0;
}
