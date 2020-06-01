/*================================================================
*   Copyright (C) 2020 Renleilei. All rights reserved.
*   
*   文件名称：235_diamond_inheritance.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2020年06月01日
*   描    述：测试菱形继承、类的大小、虚函数等相关概念
*   版    本: Version 1.00
*   编译指令: g++ -o main 235_diamond_inheritance.cpp -std=c++11
================================================================*/

#include <iostream>

using namespace std;

class Base {
public:
    Base() = default;
    virtual ~Base() = default;      // 虚函数会多一个虚表指针；1，如果是空类，大小为1；2，如果包含虚函数指针，大小为4；

private:
    //int             m_personVal = 0;            // 加上成员变量大小为 8;
    //std::string     m_strVal = "";              // 如果仅有一个string成员变量, 大小为24, 
};

class Derived : public Base {
public:
    Derived() = default;
    ~Derived() = default;       // 仅继承Base类, 且只有构造和析构函数的情况下, 大小为4

public:
    //const static int m_iVal = 1;   // 这个static的变量不影响类大小 大小为4
    //int m_iVal1 = 0;               // 非static的变量大小为 8
};

class Derived1 : virtual public Base {      // 这个 virtual public 是为了解决菱形继承中存在多个基类的情况
public:
    Derived1() = default;
    ~Derived1() = default;
};

class A {
public:
    A() { std::cout << ":: A 构造" << std::endl; }
    virtual ~A() { std::cout << ":: A 析构" << std::endl; }

public:
    void printA() { std::cout << "A::" << __func__ << std::endl; }
};

class B : virtual public A {
public:
    B() { std::cout << ":: B 构造" << std::endl; }
    ~B() { std::cout << ":: B 析构" << std::endl; }
};

class C : virtual public A {
public:
    C() { std::cout << ":: C 构造" << std::endl; }
    ~C() { std::cout << ":: C 析构" << std::endl; }
};

class D : public B, public C {
    // 如果B和C不使用virtual public A, 而使用普通的 public A, 则会引起菱形继承问题, 在D中会存在二义性, 两个A基类.
public:
    D() { std::cout << ":: D 构造" << std::endl; }
    ~D() { std::cout << ":: D 析构" << std::endl; }
};

int main()
{
	cout << "test 菱形继承 begin!!" << endl;

	cout << "Base size: " << sizeof(Base) << endl;
	cout << "Derived size: " << sizeof(Derived) << endl;
	cout << "Derived1 size: " <<sizeof(Derived1) << endl;

	D d;
	d.printA();
	return 0;
}
