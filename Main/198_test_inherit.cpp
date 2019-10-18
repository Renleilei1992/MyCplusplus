/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：198_test_inherit.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年10月18日
*   描    述：测试C++11的新特性：继承构造函数
*   版    本: Version 1.00
*   参考文献: https://mp.weixin.qq.com/s/BGUa7-RSCtFRnBYjUVFFDA (C++11新特性（59）- 继承的构造函数)
*   编译指令: g++ -o main 198_test_inherit.cpp -std=c++11
================================================================*/

#include <iostream>

using namespace std;

class Base
{
public:
	Base() = default;
	Base(int x) :m_x(x), m_y(0){}
	Base(int x, int y) :m_x(x), m_y(y){}

	virtual void printValue()
	{
		cout << "Base::" << __func__ << " m_x: " << m_x << " m_y: " << m_y << endl;
	}

public:
	int m_x = 0;
	int m_y = 0;
};

class Base_1
{
public:
	Base_1() = default;
	Base_1(int x) :m_valX(x), m_valY(0){}
	Base_1(int x, int y) :m_valX(x), m_valY(y){}

	virtual void printValue_1()
	{
		cout << "Base_1::" << __func__ << " m_valX: " << m_valX << " m_valY: " << m_valY << endl;
	}
public:
	int m_valX = 0;
	int m_valY = 0;
};

class Sub : public Base
{
public:
	Sub():Base(){}
	Sub(int x) :Base(x){}
	Sub(int x, int y) :Base(x, y){}

	virtual void printValue()
	{
		cout << "Sub::" << __func__ << " m_x: " << m_x << " m_y: " << m_y << endl;
	}

};

class Sub_1 : public Base, public Base_1
{
public:
	using Base::Base;	// 一行代码即可实现完整继承到基类的所有构造函数, 不再和Sub类中的方法一样重复编写
	using Base_1::Base_1;

	// 解决编译错误 conflicts with version inherited
	Sub_1(int x):Base(x), Base_1(x){}
	Sub_1(int x, int y):Base(x, y), Base_1(x, y){}
};

int main()
{
	Base b1(7, 8);
	b1.printValue();

	Sub s1(17, 9);
	s1.printValue();

	Sub_1 s2(88, 99);
	s2.printValue();
	s2.printValue_1();

	return 0;
}

/*
class CRect
{
public:
	CRect() = default;
	CRect(int l, int t, int r, int b)
		:leftTop(l, t)
		,rightBottom(r, b)
	{
	}
	CRect(CPoint lt, CPoint rb)
		:leftTop(lt)
		,rightBottom(rb)
	{
	}
	CRect(CPoint lt, CSize sz)
		:leftTop(lt)
		,rightBottom(lt.x + sz.cx, lt.y + sz.cy)
	{
	}
private:
	CPoint leftTop;
	CPoint rightBottom;
};
*/
