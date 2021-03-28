/*================================================================
*   Copyright (C) 2021 Renleilei. All rights reserved.
*   
*   文件名称：254_test_enable_shared_from_this.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2021年03月28日
*   描    述：测试C++11新特性 enable_shared_from_this
*   版    本: Version 1.00
================================================================*/

#include <memory>
#include <iostream>

using namespace std;

class WrongUse
{
public:
	WrongUse() = default;
	~WrongUse() { cout << "WrongUse::~WrongUse() be called!" << endl; }

	std::shared_ptr<WrongUse> getPtr() {
		return std::shared_ptr<WrongUse>(this);
	}
};

// 继承 std::enable_shared_from_this
class CorrectUse : public std::enable_shared_from_this<CorrectUse>
{
public:
	CorrectUse() = default;
	~CorrectUse() { cout << "CorrectUse::~CorrectUse() be called!" << endl; }

	std::shared_ptr<CorrectUse> getPtr() {
		return shared_from_this();
	}
};


int main(int argc, char* argv[])
{
	// 错误示例: 会引起 double free. 引用计数为1，但是会触发两次 use_count - 1
	//std::shared_ptr<WrongUse> ptr1 = std::make_shared<WrongUse>();
	//std::shared_ptr<WrongUse> ptr2 = ptr1->getPtr();
	
	// 正确示例: 析构次数为1, 引用计数为2.
	std::shared_ptr<CorrectUse> ptr1 = std::make_shared<CorrectUse>();
	std::shared_ptr<CorrectUse> ptr2 = ptr1->getPtr();

	std::cout << "ptr1's use_count() = " << ptr1.use_count() << std::endl;
	std::cout << "ptr2's use_count() = " << ptr2.use_count() << std::endl;

	return 0;
}
