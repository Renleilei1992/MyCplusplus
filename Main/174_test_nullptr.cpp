/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：174_test_nullptr.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年08月20日
*   描    述：
*   版    本: Version 1.00
================================================================*/

#include <iostream>
#include <cassert>

using namespace std;

void F(int a) {
    cout << a << endl;
}
    
void F(int *p) {
//    assert(p != NULL);	// will assert, when p == nullptr, that means nullptr == NULL
	if (p == NULL) { 
		cout << __func__ << " nullptr equal to NULL!" << endl;
	} else {
		cout << __func__ << " nullptr not equal to NULL!" << endl;
	}
    cout << __func__ << " " << p << endl;
}
    
int main() {
    int *p = nullptr;
    int *q = NULL;
    bool bEqual = (p == q); //
	cout << "bEqual = " << bEqual << endl;
//    int a = nullptr;        // c++11 编译失败,无法转型成为int
    F(0);                   // c++98 编译失败, 有二义性, c++11中会调用F(int)
    F(nullptr);             // c++11 会调用 F(int *p)

	// test _STDC_HOSTED__  & __STDC__ & __STDC_VERSION__ & __STDC_ISO_10646__
	cout << __func__ << " Standard C lib:    " << __STDC_HOSTED__ << endl;
	cout << __func__ << " Standard C:        " << __STDC__ << endl;
//	cout << __func__ << " C Standard Version:" << __STDC_VERSION__ << endl;		// error: ‘__STDC_VERSION__’ was not declared in this scope
	cout << __func__ << " ISO/IEC:           " << __STDC_ISO_10646__ << endl;
}
