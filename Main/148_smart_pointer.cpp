/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：148_smart_pointer.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年07月23日
*   描    述：
*   版    本: Version 1.00
================================================================*/

#include <memory>
#include <iostream>

using namespace std;

int main()
{
	cout << "--------- this program just show the smart pointer using -----------" << endl;

	// auto_ptr(c++98, abandoned by c++11)

	unique_ptr<int> iPtr1(new int(1));
//    unique_ptr<int> iPtr2 = iPtr1;          // error, 不能被复制
    unique_ptr<int> iPtr3 = move(iPtr1);    // ok
	if (iPtr1 == nullptr) { cout << "iPtr1 be moved, its a nullptr!" << endl; }
    iPtr3.reset();                          // 显式内存释放
	if (iPtr3 == nullptr) { cout << "iPtr3 be reset, its a nullptr!" << endl; }


	shared_ptr<int> sPtr1(new int(2));      // 引用计数法实现GC
    shared_ptr<int> sPtr2 = sPtr1;          // ok, 引用计数+1
    weak_ptr<int> wPtr = sPtr1;             // ok, 引用计数不增加
    
    cout << "sPtr1: " << *sPtr1 << endl;
    cout << "sPtr2: " << *sPtr2 << endl;
//    cout << "wPtr1: " << *wPtr << endl;		// error, no matching for <<

	sPtr1.reset();                          // 引用计数-1, 该内存区域不释放
//    cout << "sPtr1: " << *sPtr1 << endl;	// Segmentation fault
    cout << "sPtr2: " << *sPtr2 << endl;
    cout << "wPtr1: " << *wPtr.lock() << endl;

	sPtr2.reset();                          // 引用计数-1，该内存区域被释放??
    if(wPtr.lock() == nullptr) { cout << "wp is nullptr!!" <<endl; }
	return 0;
}
