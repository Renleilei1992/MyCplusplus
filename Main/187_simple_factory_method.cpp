/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：187_simple_factory_method.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年08月29日
*   描    述：简单工厂模式测试
*   版    本: Version 1.00
*   编译指令: g++ -o main 187_simple_factory_method.cpp -std=c++11
================================================================*/

#include <iostream>

using namespace std;

void test_SimpleFactory_method();
void test_factory_method();

enum PTYPE {
	PTYPE_A,
	PTYPE_B,
	PTYPE_C,
};

class Product
{
public:
	virtual void show() = 0;
};

class Product_A : public Product
{
public:
	virtual void show() override {
		cout << "Product_A::" << __func__ << endl;
	}
};

class Product_B : public Product
{
public:
	virtual void show() override {
		cout << "Product_B::" << __func__ << endl;
	}
};

// 简单工厂模式: 客户需要生产什么产品，需要给我们明确的产品类型用于生产
class Factory
{
public:
	Product* CreateProduct(PTYPE eType) {
		if (eType == PTYPE_A) {
			return new Product_A;
		} else if (eType == PTYPE_B) {
			return new Product_B;
		} else {
			cout << __func__ << " cant make this type of product!" << endl;
		}

		return nullptr;
	}
};

// 工厂模式: 一个工厂虚基类, 每一个产品对应一个工厂类, 所有工厂类均继承自这个工厂虚基类
class Factory_Base
{
public:
	virtual Product* CreateProduct() = 0;	
};

class Factory_A : public Factory_Base
{
public:
	virtual Product* CreateProduct() final {
		return new Product_A;
	}
};

class Factory_B : public Factory_Base
{
public:
	virtual Product* CreateProduct() final {
		return new Product_B;
	}
};

int main()
{
	test_SimpleFactory_method();
	test_factory_method();
	return 0;
}

void test_SimpleFactory_method()
{
	cout << __func__ << "---------------------- begin." << endl;
	Factory f;
	Product* p1 = f.CreateProduct(PTYPE_B);
	if (p1 != nullptr) {
		p1->show();
	}
	Product* p2 = f.CreateProduct(PTYPE_A);
	if (p2 != nullptr) {
		p2->show();
	}
	Product* p3 = f.CreateProduct(PTYPE_C);
	if (p3 != nullptr) {
		p3->show();
	}
	cout << __func__ << "---------------------- end." << endl;
}

void test_factory_method()
{
	cout << __func__ << "---------------------- begin." << endl;
	Factory_A fa;
	Product* p1 = fa.CreateProduct();
	if (p1 != nullptr) {
		p1->show();
	}

	Factory_B fb;
	Product* p2 = fb.CreateProduct();
	if (p2 != nullptr) {
		p2->show();
	}
	
	cout << __func__ << "---------------------- end." << endl;

}
