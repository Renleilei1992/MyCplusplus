
// 主线程里起两个子线程
#include <iostream>
#include <pthread.h>
#include <mutex>

using namespace std;

#define RETURN_MSG "child thread excute complete!"
char msg[] = "hello my child";

void *thread_function(void * arg);

int main()
{
    int res_a, res_b;
    pthread_t a_thread;
    pthread_t b_thread;
    void *thread_result;

    res_a = pthread_create(&a_thread, NULL, thread_function, (void *)msg);
    res_b = pthread_create(&b_thread, NULL, thread_function, (void *)msg);
    if (res_a == 0 || res_b == 0) {
        cout << "create thread failed!!\n";
        return -1;
    }

    return 0;
}

void *thread_function(void * arg)
{
    mutex(lock);
    //cout << "arg: " << (char *)arg << endl;;
    cout << "I'm the child thread!!\n";
    mutex(unlockpt);
    pthread_exit((void*)RETURN_MSG);
}