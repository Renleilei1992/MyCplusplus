/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：153_reinterpret_cast.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年08月05日
*   描    述：
*   版    本: Version 1.00
================================================================*/

#include <iostream>

using namespace std;

int main() 
{
    typedef void (*FunctionPointer)(int);
    int value = 21;
    const int* pointer = &value;
	cout << "pointer value: " << pointer << endl;
	cout << "&pointer: " << &pointer << endl;
	cout << "*pointer: " << *pointer << endl;
	cout << "value: " << value << endl;
	cout << "&value: " << &value << endl;
    
    //int * pointer_r = reinterpret_cast<int*> (pointer); 
    // Error: reinterpret_cast from type 'const int*' to type 'int*' casts away constness
 
    FunctionPointer funcP = reinterpret_cast<FunctionPointer> (pointer);

	cout << "-----------> after:" << endl;   
	cout << "funcP: " << &funcP << endl;
	cout << "*funcP: " << *funcP << endl;
	cout << "funcP: " << funcP << endl;
}
