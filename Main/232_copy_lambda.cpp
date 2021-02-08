/*================================================================
*   Copyright (C) 2020 Renleilei. All rights reserved.
*   
*   文件名称：232_copy_lambda.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2020年05月21日
*   描    述：拷贝构造\赋值 的展示demo
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

class CBase
{
public:
	CBase(int value) {
        cout << "CBase::" << __func__ << "----> construction be called! " << endl;
		a = value;
	}

	CBase(const CBase &b){
        cout << "CBase::" << __func__ << "----> copy construction be called! " << endl;
		a = b.a;
	}

	void show() {
		cout << "CBase::" << __func__ << ":: a = " << a << endl;
	}

private:
	int a = 0;
};

class CTest
{
public:
	void print() {
		cout << __func__ << ":: be called!" << endl;
		auto func1 = std::bind([this]()->void { 
			cout << __func__ << ":: lambda begin!" << endl;
			//std::vector<Base> vec;
			//vec.emplace_back(m_bObj);

			//m_bObj = std::move(Base("Hello CTest"));
			//CBase cb1(100);
			//m_cbObj = cb1;	// = 赋值预算符
			CBase cb2 = m_cbObj;// 拷贝构造函数
			cout << __func__ << ":: lambda end!" << endl;
			return;
		});

		func1();
	}

	void print2(){
		//cout << __func__ << ":: " << m_bObj.m_str << endl;
		m_cbObj.show();
	}

private:
//	Base m_bObj = std::move(Base("hello world!"));
	CBase m_cbObj = CBase(9);
};


int main()
{
	
	CTest	testObj;
	testObj.print();
	testObj.print2();
	return 0;
}
