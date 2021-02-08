/*================================================================
*   Copyright (C) 2020 Renleilei. All rights reserved.
*   
*   文件名称：236_calClassSize.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2020年06月14日
*   描    述：计算类的大小(各种情况)
*   版    本: Version 1.00
================================================================*/

#include <iostream>

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
    std::cout << "Hello World!\n"; 

#ifdef  _RD
    std::cout << "dpi = " << dpiInfoObj.getMonitorDpi() << std::endl;
#endif //  _RD


    std::string str("Hello C++! 111111111111111111111");
    std::cout << "Base: " << sizeof(Base) << std::endl;
    std::cout << "Derived: " << sizeof(Derived) << std::endl;
    std::cout << "Derived1: " << sizeof(Derived1) << std::endl;
    std::cout << "string " << sizeof(std::string) << std::endl;
    std::cout << "string.size(): " << str.size() << " length: " << str.length() << " max_size: " << str.max_size() << " capacity: " << str.capacity() << std::endl;

    // 测试菱形继承问题.
    D d;
    //d.printA();

    return 0;
}
