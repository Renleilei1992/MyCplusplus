/*================================================================
*   Copyright (C) 2018 Renleilei. All rights reserved.
*   
*   文件名称：026_operator.cpp
*   创 建 者：Renleilei (renleilei@foxmail.com)
*   创建日期：2018年01月26日
*   描    述：
*   版    本: Version 1.00
================================================================*/

#include <iostream>

using namespace std;

class Rational
{
	public:
		Rational();
		~Rational();
		const Rational operator* (const Rational& lhs, const Rational& rhs) { return lhs * rhs; }

	public:
		int a;
}

int main()
{
	int a = 5;
	int b = 6;

	Rational a = 5;
	Rational b = 6;

	Rational ans = operator* (a, b);

	cout<<ans<<endl;

	return 0;
}

