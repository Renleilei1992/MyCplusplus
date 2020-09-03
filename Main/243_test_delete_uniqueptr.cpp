/*================================================================
*   Copyright (C) 2020 Renleilei. All rights reserved.
*   
*   文件名称：243_test_delete_uniqueptr.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2020年09月03日
*   描    述：
*   版    本: Version 1.00
*   编译指令: g++ -o main 243_test_delete_uniqueptr.cpp -std=c++14
================================================================*/

#include <iostream>
#include <memory>

using namespace std;

class A
{
public:
	A(){
		cout << __func__ << "construction be called!" << endl;
	}

	~A(){
		cout << __func__ << "deconstruction be called!" << endl;
	}
};

int main()
{
	std::unique_ptr<A> ptrA = std::make_unique<A>();

	// 主动删除: 可以生效，触发~A()
	//ptrA = nullptr;

	// 主动删除: 可以生效, 触发~A()
	//ptrA.reset(nullptr);

	// 主动删除: 可以生效, 触发~A()
	A* ptrA1 = ptrA.release();
	if (ptrA1 != nullptr) {
		delete ptrA1;
	}

	cout << "flag!" << endl;

	return 0;
}
