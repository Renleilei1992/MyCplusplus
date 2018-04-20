/*================================================================
*   Copyright (C) 2018 Renleilei. All rights reserved.
*   
*   文件名称：037_virtualDestructorsFunction.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2018年03月15日
*   描    述：
*   版    本: Version 1.00
*   编译命令: 
================================================================*/


#include <iostream>

using namespace std;

class TimeKeeper
{
	public:
		TimeKeeper()
		{
			cout<<"TimeKeeper Contructor working..."<<endl;
		}
		virtual ~TimeKeeper();
//		~TimeKeeper()
//		{
//			cout<<"TimeKeeper Destructor working..."<<endl;
//		}
};

class AtomicClock: public TimeKeeper
{
	public:
		AtomicClock()
		{
			cout<<"AtomicClock Contructor working..."<<endl;
		}
		virtual ~AtomicClock();
//	 	~AtomicClock()
//		{
//			cout<<"AtomicClock Destructor working..."<<endl;
//		}
};

int main()
{
//	TimeKeeper* pt01 = new TimeKeeper();
  AtomicClock* pt02 = new AtomicClock();

	delete pt02;
//	delete pt01;
	return 0;
}
