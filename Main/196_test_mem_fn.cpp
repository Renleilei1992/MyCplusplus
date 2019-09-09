/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：196_test_mem_fn.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年09月09日
*   描    述：简单测试C++11新特性中的mem_fn类模板
*   版    本: Version 1.00
*   参考文献: [C++11新特性(84)-标准库mem_fn类模板](https://blog.csdn.net/craftsman1970/article/details/83096914)
================================================================*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

void func01();
void func02();

struct Foo {
	Foo(int val):data{val} {}
	bool compare(const Foo& t) const {
		return (data < t.data);
	}

	int data;
};

bool compare(const Foo& f1, const Foo& f2) {
	return f1.compare(f2);
}

class FooPrint {
public:
	void print() { cout << __func__ << "::data = " << data << endl; }
	//void print(int i) { cout << __func__ << "::data = " << data << " i = " << i << endl; }

	int data{100};
};

int main()
{
//	func01();
	func02();

	return 0;
}

void func01()
{
	std::vector<Foo> fv{1, 6, 3, 2, 8};
	for (auto ivec : fv) { cout << ivec.data; }
	cout << endl;

	// 多种方法可以进行排序

	// 普通方法1: 需要声明一个比较函数
//	sort(fv.begin(), fv.end(), compare);

    // 普通方法2: 也可以使用匿名函数进行比较
//	sort(fv.begin(), fv.end(), [](const Foo& f1, const Foo& f2){ return f1.compare(f2); });

	// 普通方法3: 使用C++11的function模板生成可以调用的对象
//	function<bool(const Foo&, const Foo&)> fcomp = &Foo::compare;
//	sort(fv.begin(), fv.end(), fcomp);

	// 普通方法4: 使用C++11的mem_fn生成调用对象
	sort(fv.begin(), fv.end(), mem_fn(&Foo::compare));
	for (auto ivec : fv) { cout << ivec.data; }
	cout << endl;
}

void func02()
{
//	std::vector<int> iv{10, 99, 88, 66, 25};

	cout << __func__ << "::obj for_each..." << endl;
	std::vector<FooPrint *> fpv;
	fpv.push_back(new FooPrint());
	fpv.push_back(new FooPrint());
	fpv.push_back(new FooPrint());
	fpv.push_back(new FooPrint());
	fpv.push_back(new FooPrint());

	for_each(fpv.begin(), fpv.end(), mem_fn(&FooPrint::print));

	for_each(fpv.begin(), fpv.end(), [&](FooPrint* fp){
		delete fp;
		fp = nullptr;
	});

	cout << __func__ << "::obj for_each..." << endl;
	std::vector<FooPrint> fv;
	fv.push_back(FooPrint());
	fv.push_back(FooPrint());
	fv.push_back(FooPrint());
	fv.push_back(FooPrint());
	fv.push_back(FooPrint());

	for_each(fv.begin(), fv.end(), mem_fn(&FooPrint::print));
}
