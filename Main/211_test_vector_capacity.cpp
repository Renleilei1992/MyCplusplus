/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：211_test_vector_capacity.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年11月02日
*   描    述：简单测试vector自动扩容时存储的指针和对象的区别
*   版    本: Version 1.00
*   编译指令: g++ -o main 211_test_vector_capacity.cpp -std=c++14
================================================================*/

/*
	总结: 1，如果是指针不会触发析构; 2, 如果是对象,会触发析构和拷贝构造
*/

#include <iostream>
#include <vector>
#include <memory>	// std::unique_ptr std::make_unique

using namespace std;

class A
{
public:
	A() { cout << "A::construct!" << endl; }
	~A() { cout << "A::deConstruct!" << endl; }

	explicit A(const A& a) { cout << "A::copy!!" << endl; }
};

int main()
{
	std::vector<A*> vec_1;
	A* a1 = new A();
	A* a2 = new A();
	A* a3 = new A();

	cout << "-----------------------ptr begin push_back --------------------------" << endl;
	vec_1.push_back(a1);
	cout << "capacity: " << vec_1.capacity() << endl;
	vec_1.push_back(a2);
	cout << "capacity: " << vec_1.capacity() << endl;
	vec_1.push_back(a3);
	cout << "capacity: " << vec_1.capacity() << endl;
	cout << "-----------------------ptr end push_back --------------------------" << endl;


	std::vector<A> vec_2;
	A b1, b2, b3, b4, b5;
	
	cout << "-----------------------obj begin push_back --------------------------" << endl;
	vec_2.push_back(b1);
	cout << "capacity: " << vec_2.capacity() << endl;
	vec_2.push_back(b2);
	cout << "capacity: " << vec_2.capacity() << endl;
	vec_2.push_back(b3);
	cout << "capacity: " << vec_2.capacity() << endl;
	cout << "-----------------------end begin push_back --------------------------" << endl;

	std::vector<std::unique_ptr<A>> vec_3;
	cout << "-----------------------unique_ptr begin emplace_back --------------------------" << endl;
	vec_3.emplace_back(std::make_unique<A>());
	cout << "capacity: " << vec_3.capacity() << endl;
	vec_3.emplace_back(std::make_unique<A>());
	cout << "capacity: " << vec_3.capacity() << endl;
	vec_3.emplace_back(std::make_unique<A>());
	cout << "capacity: " << vec_3.capacity() << endl;
	cout << "-----------------------unique_ptr end emplace_back --------------------------" << endl;


	cout << "---------------> delete vec_1 begin" << endl;
	for (auto iVec : vec_1) {
		if (iVec != nullptr) {
			delete iVec;
		}
	}
	cout << "---------------> delete vec_1 end" << endl;
	return 0;
}
