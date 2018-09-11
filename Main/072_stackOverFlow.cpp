/*================================================================
*   Copyright (C) 2018 Renleilei. All rights reserved.
*   
*   文件名称：072_stackOverFlow.cpp
*   创 建 者：Renleilei (renleilei@foxmail.com)
*   创建日期：2018年08月17日
*   描    述：
*   版    本: Version 1.00
================================================================*/

#include <iostream>

using namespace std;

void fun_01(int n) throw(int );
void fun_02(int n) throw(bool );

int main()
{
	try{
		fun_02(2896);
	}
	catch(bool ){
		cout << "001==========> stack over flow" << endl;
	}
	catch(...){
		cout << "002==========> stack over flow" << endl;
	}

	return 0;
}

void fun_01(int n) throw(int )
{
	cout << "func_01 start ...." << endl;
	int len = n;
	bool pd[len][len];
	for (int i = 0; i < len; i++)
		for (int j = 0; j < len; j++)
			pd[i][j] = true;
}

void fun_02(int n) throw(bool )
{
	cout << "fun_02 start..." << endl;
	if(n > 10){
		throw(false);
	}
}
