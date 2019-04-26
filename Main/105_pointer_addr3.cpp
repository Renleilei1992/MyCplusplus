/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：105_pointer_addr3.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年04月26日
*   描    述：
*   版    本: Version 1.00
================================================================*/

#include <iostream>

using namespace std;

class A
{
public:
	A(){
		cout << "A's construction.." << endl;
	}
	~A(){
		cout << "A's deconstruction.." << endl;
	}
	void showVal(){
		cout << "A's m_val01 = " << m_val01 << endl;
	}
	void setVal(int val){
		m_val01 = val;
	}


private:
	int m_val01;

};

int main()
{
	A* a1 = new A();
	if (a1 != NULL) {
		a1->setVal(100);
		a1->showVal();
	}

	A* a2 = a1;
	if (a2 != NULL) {
		a2->showVal();
	}

	if(a1 != NULL) {
		delete a1;
		//delete a1;	// 多次释放堆空间会造成堆破坏
		a1 = NULL;
	}

	A* a3 = new A();	// 观察可得当a1被释放后,由于a3和a1使用内存完全一致,a1被释放的内存地址会给到a3使用;(表现为a3的地址与a1释放前一致)

	a2->showVal();		// Linux下会显示0, Windows VS编译器会优化为 0xddddddd 
	a2->setVal(200);
	a2->showVal();		// a2指针依旧可以对其赋值成功,并且对该内存进行操作
	a3->showVal();		// a3指针由于依旧使用的a1释放前的地址, 该地址的内容被a2改写了, 所以此处打印出来的值是 200


	return 0;
}
