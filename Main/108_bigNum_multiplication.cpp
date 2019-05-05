/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：108_bigNum_multiplication.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年04月27日
*   描    述：大数相乘
*   版    本: Version 1.00
*   参考文献: https://blog.csdn.net/u010983881/article/details/77503519
*   参考解法: https://www.nowcoder.com/questionTerminal/0f0badf5f2204a6bb968b0955a82779e
================================================================*/

#include <iostream>
#include <string>

using namespace std;

const int L = 11000;

// 自定义的数组长度计算函数模板
template<class T>
int length(T &arr){
	return sizeof(arr) / sizeof(arr[0]);
}


int getNumLength(long num)
{
	int i = 0;
	while(num != 0){
		i++;
		num /= 10;
	}

	return i;
}


// 分治算法: Karatsuba算法 TBD
long multiBigNum(long num1, long num2)
{
	// 递归终止条件
	if(num1 < 10 || num2 < 10) return num1 * num2;

	// 计算拆分长度
	int size1 = getNumLength(num1);
	int size2 = getNumLength(num2);
	int halfN = size1 >= size2 ? size1/2 : size2/2;

	// 拆分为 a, b, c, d
	long a = 1;
	
}

string mul(string a, string b)
{
	string s;
	int na[L], nb[L], nc[L], La=a.size(), Lb=b.size(),i,j;
	fill(na, na+L, 0);		// na: {0, 0, 0, 0, 0 ...}
	fill(nb, nb+L, 0);		// nb: {0, 0, 0, 0, 0 ...}
	fill(nc, nc+L, 0);		// nc: {0, 0, 0, 0, 0 ...}

	cout << "测试: a[La-1]: " << a[La-1] << " a[La-1] - '0': " << a[La-1] - '0'	<< endl;

	// 以下两个for循环旨在将字符串分别写入数组中, 至于为何使用 -'0' 的操作, 暂时还不知道原因;
	for(i=La-1; i>=0; i--){ na[La-i] = a[i] - '0'; }
	for(i=Lb-1; i>=0; i--){ nb[Lb-i] = b[i] - '0'; }

	// a和b每个字符串的每个字符进行相乘,并记录结果到nc数组中
	for(i=1; i<=La; i++) {
		for(j=1; j<=Lb; j++) {
			nc[i+j-1] += na[i]*nb[j];
			cout << "na[" << i << "] * nb[" << j << "] 累计为: nc[" << i+j-1 << "] = " << nc[i+j-1] << endl;
		}
	}

	// 进行进位处理, 从低位到高位
	for(i=1; i<=La+Lb; i++) {
		cout << "----进位计算前: nc[" << i << "] = " << nc[i] << "  nc[" << i << "]/10 = " << nc[i]/10 << "  nc[" << i << "]%10 = " << nc[i]%10 << endl;
		nc[i+1] += nc[i]/10,nc[i]%=10;
		cout << "----进位计算后: nc[" << i << "] = " << nc[i] << "   nc[" << i+1 << "] = " << nc[i+1] << "  nc[" << i << "]/10 = " << nc[i]/10 << "  nc[" << i << "]%10 = " << nc[i]%10 << endl;
		cout << "==== 分割线 ====" << endl;
	}

	// 检测最高位是否为0
	if(nc[La+Lb]) {
		cout << "组装结果字符串: nc[La+Lb]: " << nc[La+Lb] << endl;
		s += nc[La+Lb] + '0';
	}

	// 将nc数组中的结果倒序组装进入结果字符串中
	for(i=La+Lb-1; i>=1; i--) {
		s += nc[i] + '0';
	}

	cout << "mul function end... string s = " << s << endl;
	return s;
}


int main()
{
	int a = 123;
	int b = 456;

	cout << "a*b = " << a*b << endl;

	int _a[] = {1, 2, 3};
	int _b[] = {4, 5, 6};

	cout << "_a 数组: ";
	for(int i = 0; i < sizeof(_a)/sizeof(int); ++i) {
		cout << _a[i] << " ";
	}
	cout << "长度为: " << length(_a) << endl;

	cout << "_b 数组: ";
	for(int i = 0; i < sizeof(_b)/sizeof(int); ++i) {
		cout << _b[i] << " ";
	}
	cout << "长度为: " << length(_b) << endl;

	cout << "--------- 使用一个大佬的AC代码: " << endl;
	string s1 = "123";
	string s2 = "456";
	cout << s1 << " * " << s2 << " = " << mul(s1, s2) << endl;

	return 0;
}
