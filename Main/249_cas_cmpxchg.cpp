/*================================================================
*   Copyright (C) 2020 Renleilei. All rights reserved.
*   
*   文件名称：249_cas_cmpxchg.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2020年12月14日
*   描    述：探寻cas的汇编实现 (不知道如何编译通过)
*   版    本: Version 1.00
================================================================*/

#include <iostream>

using namespace std;
int main(){
	int a=0,b=0,c=0;
 
	__asm{
		mov eax,100;
		mov a,eax
	}
	cout << "a := " << a << endl;
	b = 99;
	c = 11;
	__asm{
		mov ebx,b
		cmpxchg c,ebx
		mov a,eax    
	}
	cout << "b := " << b << endl;
	cout << "c := " << c << endl;
	cout << "a := " << a << endl;
	return 0;
}
