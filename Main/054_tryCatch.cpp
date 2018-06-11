/*================================================================
*   Copyright (C) 2018 Renleilei. All rights reserved.
*   
*   文件名称：054_tryCatch.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2018年05月28日
*   描    述：
*   版    本: Version 1.00
*   编译命令: 
================================================================*/

#include <iostream>
#include <exception>

using namespace std;

class myException_01 : public exception
{
	virtual const char* what() const throw()
	{
		return "My exception happend! The number you input is bigger than 10, plz retry!!";
	}
}myex_01;

class myException_02 : public exception
{
	virtual const char* what() const throw()
	{
		return "The number you input is smaller than 0, plz retry!!";
	}
}myex_02;

int main(int argc, char** argv)
{
	int val_01 = 3;
	int val_02;
	cout<<"Plz input integer number: "<<endl;

	try{
		cin>>val_02;
		if(val_02 > 10){
//			throw input_big_error("the number you input big than 10, plz minilized it!!");
			throw myex_01;
		}else if(val_02 < 0){
//			throw input_small_error("the number you input smaller than 0, plz input the correct number again!!");
			throw myex_02;
		}
	}catch(exception &e){
		cout<<e.what()<<endl;
	}


/*
	}catch(input_big_error err){
		cout<<err<<endl;
	}catch(input_small_error err){
		cout<<err<<endl;
	}
*/

	return 0;
}
