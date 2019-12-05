/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：210_test_shared_ptr_loopRef.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年11月02日
*   描    述：测试智能指针shared_ptr的循环引用问题
*   版    本: Version 1.00
*   参考链接: [动态内存与智能指针](https://blog.csdn.net/river_lethe/article/details/78733914)	// 此文的循环引用方式也值得一看
================================================================*/

#include <iostream>
#include <memory>
class A;
class B;
class A {
public:
//	std::shared_ptr<B> pointer;		// 如果两个均为 shared_ptr 强引用会造成循环引用，两个引用计数均为2, 无法正确析构
	std::weak_ptr<B> pointer;		// 如果两个类中其中一个为 weak_ptr 弱引用, 不增加其引用计数
	~A() {
		std::cout << "A 被销毁" << std::endl;
	}
};
class B {
public:
	std::shared_ptr<A> pointer;
	~B() {
		std::cout << "B 被销毁" << std::endl;
	}
};
int main() {
	std::shared_ptr<A> a = std::make_shared<A>();
	std::shared_ptr<B> b = std::make_shared<B>();
	a->pointer = b;
	b->pointer = a;
	return 0;
}
