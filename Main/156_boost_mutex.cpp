/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：156_boost_mutex.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年08月09日
*   描    述：
*   版    本: Version 1.00
================================================================*/

#include <iostream>
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>

boost::mutex mutex;
boost::mutex io_mutex;
int count = 0;

void Counter() {

  int i;
  {
//    boost::unique_lock<boost::mutex> lock(mutex);
    i = ++count;
  }
  
  {
//    boost::unique_lock<boost::mutex> lock(io_mutex);
    std::cout << "count == " << i << std::endl;
  }
}

int main() {
  boost::thread_group threads;
  for (int i = 0; i < 4; ++i) {
    threads.create_thread(&Counter);
  }

  threads.join_all();
  return 0;
}
