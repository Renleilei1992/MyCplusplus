/*================================================================
*   Copyright (C) 2018 Renleilei. All rights reserved.
*   
*   文件名称：065_pointer_addr.cpp
*   创 建 者：Renleilei (renleilei@foxmail.com)
*   创建日期：2018年06月19日
*   描    述：
*   版    本: Version 1.00
================================================================*/

#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

/*
template <typename T>
void print(T i) {
    cout<<i<<endl;
	printf("指针的地址为: 0X%p\n", i);
}
*/

class A
{
public:
	A(int *p){
		m_p = p;
	}

	~A();

	void print(){
		printf("A 类中指针地址为: 0X%p\n", m_p);
		*m_p = 3;
	}
public:
	int *m_p;
};

int main()
{
	int i = 1;
	int *p = &i;

/*
	print(*p);

	*p = 2;
	
//	print(i);

	print(*p);

	int j = 10;
	p = &j;

	print(*p);	
*/

	printf("指针P的地址为: 0X%p\n", &i);
	A* a = new A(&i);
	a->print();

	if(a){
		free(a);
	}

	cout<< i << "    " <<&i<<endl;
	return 0;
}
