/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：179_test_enum.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年08月23日
*   描    述：测试使用c++11类型安全的新枚举用法 (强类型枚举)
*   版    本: Version 1.00
================================================================*/

/*
	总结: 
		1, C++03中枚举类型不是类型安全的,枚举类型被视为整数,两种枚举类型可以进行比较; c++11引入枚举类,此种枚举类型安全,不能隐式转换为整数,也无法与整数值进行比较,(MyEnum_Val4 == 101 会触发编译错误);
		2, 枚举类默认类型为int, 倘若指定其他类型: enum class MyEnum2 : unsigned int
		3, c++11允许给传统的枚举指定类型: enum MyEnum3 : unsigned long
		4, 强作用域 MyEnum::MyEnum_Val1
		5, enum class 与 enum struct 没有任何区别
*/

#include <iostream>

using namespace std;

enum class MyEnum
{
	MyEnum_Val1,
	MyEnum_Val2,
	MyEnum_Val3 = 100,
	MyEnum_Val4 /* = 101 */,
};

enum Type : int
{
	Type_General,
	Type_Light,
};

int main()
{
//	cout << "MyEnum_Val1: " << MyEnum::MyEnum_Val1 << endl;		// 需要重载 << 
//	if (MyEnum::MyEnum_Val3 == 100) {							// no match for ‘operator==’ (operand types are ‘MyEnum’ and ‘int’)
//		cout << "MyEnum_Val3 == 100!!" << endl;
//	}

	MyEnum e1 = MyEnum::MyEnum_Val3;

	switch(e1) {
	case MyEnum::MyEnum_Val1:
		cout << "MyEnum_Val1 match!!" << endl;
		break;
	case MyEnum::MyEnum_Val2:
		cout << "MyEnum_Val2 match!!" << endl;
		break;
	case MyEnum::MyEnum_Val3:
		cout << "MyEnum_Val3 match!!" << endl;
		break;
	case MyEnum::MyEnum_Val4:
		cout << "MyEnum_Val4 match!!" << endl;
		break;
	default:
		cout << "no match!!" << endl;
		break;
	}

	Type t1 = Type_General;
	Type t2 = Type::Type_Light;

	cout << t1 << endl;

	return 0;
}
