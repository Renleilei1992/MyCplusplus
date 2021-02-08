/*================================================================
*   Copyright (C) 2021 Renleilei. All rights reserved.
*   
*   文件名称：253_test_future.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2021年02月08日
*   描    述：测试std::future C++11新特性,异步起线程的方式
*   版    本: Version 1.00
================================================================*/

void testFunc() {
	//通过async来获取异步操作结果
	std::future<int>  result = std::async([](){ 
    	std::this_thread::sleep_for(std::chrono::milliseconds(500));
    	return 8; 
	});

	std::cout << "the future result : " << result.get() << std::endl;
	std::cout << "the future status : " << result.valid() << std::endl;
	try
	{
    	result.wait();  //或者 result.get() ,会异常
  		//因此std::future只能用于单线程中调用 多线程调用使用std::share_future();
	}
	catch (...)
	{
    	std::cout << "get error....\n ";
	}
}
