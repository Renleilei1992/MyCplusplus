/*================================================================
*   Copyright (C) 2020 Renleilei. All rights reserved.
*   
*   文件名称：238_reflection_factory.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2020年06月20日
*   描    述：C++反射的一种尝试demo
*   版    本: Version 1.00
================================================================*/

#include <iostream>
#include <map>
#include <string>
#include <iomanip>

using namespace std;

class Base {
public:
	Base(){ cout << "Base construction!" << endl; }
	virtual ~Base() { cout << "Base deconstruction!" << endl; }
};

class Derived1 : public Base {
public:
	int m_a = 0;
public:
	//Derived1(int a):m_a(a) { cout << "Derived1 construction! a = " << m_a << endl; }
	Derived1() { cout << "Derived1 construction!" << endl; }
	virtual ~Derived1() override { cout << "Derived1 deconstruction!" << endl; }

	void print() { cout << "Derived1::" << __func__ << endl; }
};

class Derived2 : public Base {
public:
	int m_a = 0;
public:
	//Derived2(int a):m_a(a) { cout << "Derived2 construction! a = " << m_a << endl; }
	Derived2() { cout << "Derived2 construction!" << endl; }
	virtual ~Derived2() override { cout << "Derived2 deconstruction!" << endl; }

	void print() { cout << "Derived2::" << __func__ << endl; }
};

template<typename T> Base * createInstance() { return new T; }

typedef std::map<std::string, Base*(*)()> map_type;

class Factory {
public:
	Factory() = default;
	
	void registerClass(const std::string className) {
		// register the class name
	//	m_classMap.insert(std::make_pair(className, &createInstance<className>));
	}

	Base* create(std::string className, int arg) {
		cout << __func__ << " be called! className: " << className << endl;
		auto iter = m_classMap.find(className);
		if (iter != m_classMap.end()) {
			// not exist
			//m_classMap[className] = &createInstance<className>;
			return iter->second();
		} else {
			// exist
			cout << "Already exist class: " << className << endl;
		}
/*
		if (className == "Derived1") {
			m_classMap["Derived1"] = &createInstance<Derived1>;
			return m_classMap["Derived1"];
		} else if (className == "Derived2") {
			m_classMap["Derived2"] = &createInstance<Derived2>;
			return m_classMap["Derived2"];
		}
*/
		return nullptr;
	}

	Base* getClassInstance() {}

private:
	map_type	m_classMap;
};


int main()
{
/*
	Factory fac;
	Base* p = fac.create("Derived1", 10);
	Derived1* ptr = static_cast<Derived1>(p);
	ptr->print();
*/
	cout << "--------" << endl;

	map_type map;
	map["Derived1"] = createInstance<Derived1>;
	map["Derived2"] = &createInstance<Derived2>;

	Derived1* p1 = static_cast<Derived1*>(map["Derived1"]());
	p1->print();
	Base* p2 = map["Derived2"]();
	//p2->print();


/*
	delete p;
	p = nullptr;
*/
	delete p1;
	p1 = nullptr;
	delete p2;
	p2 = nullptr;
	return 0;
}
