/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：206_test_emplace.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年10月28日
*   描    述：C++11新特性的emplace以及emplace_back简单使用及归纳
*   版    本: Version 1.00
================================================================*/

#include <iostream>
#include <vector>
#include <functional>

using namespace std;

class Base
{
public:
	Base(std::string vStr) :m_str(std::move(vStr)) {
		cout << "Base::" << __func__ << "----> construction be called! " << endl;
	}

	~Base() {
		cout << "Base::" << __func__ << "----> deconstruction be called! " << endl;
	}

	Base(const Base &b) :m_str(std::move(b.m_str)) {
		cout << "Base::" << __func__ << "----> copy construction be called! " << endl;
	}

	Base(Base&& b) :m_str(std::move(b.m_str)) {
		cout << "Base::" << __func__ << "----> move construction be called! " << endl;
	}

public:
	std::string m_str = "";
};

int main()
{
//	Base b = Base("hello world!");
//	Base b("hello world!");
	Base b = std::move(Base("hello world!"));
	std::vector<Base> vec_1;
	std::vector<Base> vec_2;

	cout << "-----------------------> emplace_back begin ------------------" << endl;
	vec_1.emplace_back(std::string("hello world!"));
	vec_1.emplace_back(std::string("hello world!"));
	cout << "-----------------------> emplace_back end ------------------" << endl;

	cout << endl;

	cout << "-----------------------> push_back begin ------------------" << endl;
	vec_2.push_back(std::string("hello world!"));
	vec_2.push_back(std::string("hello world!"));
	cout << "-----------------------> push_back end ------------------" << endl;
	
	cout << "------------- test copy begin! --------------------" << endl;
	const Base b1 = Base("hello const copy 1!");
	Base b2 = Base("hello const copy 2!");
	//auto cb = std::bind([=]()->Base { return Base("hello copy construction!"); });
	auto func1 = std::bind([=]()->Base { return b1;});
	func1();
	Base d(func1());
	Base d1 = func1();

	cout << "----- split -------" << endl;
	Base e1("hello world!");
	//Base e2 = e1;
	auto func2 = std::bind([=]()->Base { return e1;});
	Base e3 = func2();
	
	cout << "------------- test copy end! --------------------" << endl;
	

	return 0;
}
