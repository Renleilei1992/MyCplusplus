/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：100_primeMultiplication.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年04月12日
*   描    述：
*   版    本: Version 1.00
================================================================*/

#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

// 判断一个数是否是素数
bool isPrime(int num)
{
	// 质数的特征: 总是6n+1或者6n+5 (6n\6n+2\6n+3\6n+4 均能因式分解)
	int i = 0;
	if (num < 3) {
		return num > 1;
	}

	if ((num % 6 != 1) && (num % 6 != 5)) {
		return false;
	}

	for (i = 5; i <= sqrt(num); i += 6) {
		if ((num % i == 0) || (num % (i + 2) == 0)) {
			return false;
		}
	}

	return true;
}

int checkMultiplier(int num)
{
	cout << "---- begin check ----" << endl;

	int j = 0;

	for(int i = 1; i <= sqrt(num); ++i) {
		if (isPrime(i)){
			j = num / i;
			if ((num % j == 0) && isPrime(j)){
				cout << "find it: " << num << " = " << i << " * " << j << endl;
				return 0; 
			}	
		}
	}

	cout << "---- end check ----" << endl;

	return -1;
}

int countThree(int num)
{
	int ret = 0;
	for (; num > 0; num /= 10) {
		if (num % 10 == 3){
			ret++;
		}
	}

	return ret;
}

int checkTripleTimes(int num)
{
	int count = 0;
	for (int i = 2; i <= num; ++i) {
		if(i%2 != 0){
			count = count + countThree(i);
		}
	}

	return count;
}

int main(int argc, char **argv)
{

	int p = 707829217;

	if (isPrime(p)) {
		cout << p << " 是素数!" << endl;
	} else {
		cout << p << " 不是素数!" << endl;
	}

	checkMultiplier(p);

	checkMultiplier(37254169);

	int q = 866278171; // 707829217 = 8171 * 86627

	cout << "---> 出现3的次数为: " << checkTripleTimes(q) << endl;
	
	return 0;	
}
