/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：159_boost_test3.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年08月10日
*   描    述：
*   版    本: Version 1.00
*	编译指令: g++ -o main 159_boost_test3.cpp -lboost_system -static -pthread -lboost_thread  <可以编译成功>
================================================================*/

#include <boost/thread.hpp>
#include <locale>
#include <iostream>
#include <clocale>

void wait(int seconds) {
    boost::this_thread::sleep(boost::posix_time::seconds(seconds));
}

void thread(){
    for (int i=0; i<5; ++i) {
        wait(1);
        std::cout<< i << std::endl;
    }
}

int main(){
    boost::thread t(thread);

    t.join();
    return 0;
}
