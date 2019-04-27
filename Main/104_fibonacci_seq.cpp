/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：104_fibonacci_seq.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年04月25日
*   描    述：
*   版    本: Version 1.00
*	参考文献: https://www.cnblogs.com/klchang/p/7857477.html 《斐波那契数列问题》
*	参考文献: “何海涛《剑指Offer：名企面试官精讲典型编程题》2012年”
================================================================*/

#include <iostream>
#include <cstdio>
#include <time.h>

using namespace std;

// 打印出时间戳
void showTimeFlag();
// 矩阵
long int* matrixPower(long int* mat, int n);

//方法1: 普通的递归方法求斐波那契数列的第n项 时间复杂度是 O(2^n) [计算第45项耗时8秒左右]
long calFibonacci(long n)
{
	if (n == 1) { return 1; }
	if (n == 2) { return 1; }

	long retVal = calFibonacci(n - 1) + calFibonacci(n - 2);

	return retVal;
}

//方法2: 使用迭代法求斐波那契数列的第n项 时间复杂度是 O(n) [计算第45项耗时不足1秒]
long calFibonacci_01(long n)
{
	long result = 0;
	long nextItem = 1;
	
	for (long i = 1; i <= n; ++i) {
		long tmp = nextItem;
		nextItem += result;
		result = tmp;
	}
	
	// 循环历程:
	// loop 1: tmp = 1; nextItem = 1; result = 1;	return 1;
	// loop 2: tmp = 1; nextItem = 2; result = 1;	return 1;
	// loop 3: tmp = 2; nextItem = 3; result = 2; 	return 2;
	// loop 4: tmp = 3; nextItem = 5; result = 3; 	return 3;
	// ...
	
	return result;
}

//方法3: 使用矩阵公式法计算斐波那契数列的第n项 时间复杂度是 O(logn) [计算第45项耗时不足1秒]
long fibonacciMatrixPower(long n)
{
    long int matrix[] = {1, 1, 1, 0};
    long result = 0;
    if (n <= 0)
        result = 0;
    else
    {
        matrixPower(matrix, n-1);
        result = matrix[0];
    }

    return result;
}


int main()
{
	cout << "计算long的最大值和最小值: " << endl;
	long max = 1;
	printf("sizeof(long ) = %d \n",sizeof(long)); //long类型数据占的字节数bytes
	printf("sizeof(int ) = %d \n",sizeof(int));   
	printf("sizeof(long long ) = %d \n",sizeof(long long));
	printf("Max of long is %ld \n",~(max<<(sizeof(long)*8-1)));//long 的最大值:  9223372036854775807
	printf("Min of long is %ld \n",(max<<(sizeof(long)*8-1))); //long 的最小值: -9223372036854775808

	cout << "---- program begin -----" << endl;
	cout << "计算斐波那契数列第5项: " << calFibonacci(5) << endl;	// 1 1 2 3 5 8 ...

	showTimeFlag();
	cout << "普通递归方法计算斐波那契数列第45项: " << calFibonacci(45) << endl;
	showTimeFlag();
	cout << "迭代法计算斐波那契数列第45项: " << calFibonacci_01(45) << endl;
	showTimeFlag();
	cout << "公式法计算斐波那契数列第45项: " << fibonacciMatrixPower(45) << endl;
	showTimeFlag();

	return 0;
}

void showTimeFlag()
{
	time_t t1;
    time(&t1);
    t1 = t1 + 8*3600;
    tm* t = gmtime(&t1);
//    cout << "use gmtime: " << t1 << endl;

    // man gmtime can see the struct time_t
    printf("%d-%02d-%02d %02d:%02d:%02d\n", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
}

// 2 x 2 matrix power, n >= 0
long int* matrixPower(long int *mat, int n)
{
    const int rows = 2;
    const int cols = 2;

    if (n <= 0)
        return NULL;
    else if (0 == n)
    {
        // identity matrix when the power of a matrix is 0.
        for (int i = 0; i < rows; ++i)
            for (int j = 0; i < cols; ++j)
        {
            if (i == j)
                *(mat + i * cols + j) = 1;
            else
                *(mat + i * cols + j) = 0;
        }
    }
    else if (1 == n)
    {
    }
    else if (2 == n)
    {
        // Create two temporary arrays for matrix multiplication
        long int tmpMat1[4], tmpMat2[4];
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
        {
            tmpMat1[i*cols+j] = *(mat + i * cols + j);
            tmpMat2[i*cols+j] = *(mat + i * cols + j);
        }
        // matrix multiplication
        *(mat + 0 * cols + 0) = tmpMat1[0*cols+0] * tmpMat2[0*cols+0] + tmpMat1[0*cols+1] * tmpMat2[1*cols+0]; // matrix{0,0}
        *(mat + 0 * cols + 1) = tmpMat1[0*cols+0] * tmpMat2[0*cols+1] + tmpMat1[0*cols+1] * tmpMat2[1*cols+1]; // matrix{0,1}
        *(mat + 1 * cols + 0) = tmpMat1[1*cols+0] * tmpMat2[0*cols+0] + tmpMat1[1*cols+1] * tmpMat2[1*cols+0]; // matrix{1,0}
        *(mat + 1 * cols + 1) = tmpMat1[1*cols+0] * tmpMat2[0*cols+1] + tmpMat1[1*cols+1] * tmpMat2[1*cols+1]; // matrix{1,1}
    }
    else if (n % 2 == 0)  // when n is even and n is greater than 2
    {
        matrixPower(mat, n/2);
        matrixPower(mat, 2);
    }
    else  // n is odd and n is greater than 2
    {
        long int tmpMat1[4];
        for (int k = 0; k < 4; ++k)
            tmpMat1[k] = *(mat + k);
        // Compute matrix power in even case
        matrixPower(mat, n-1);
        // Temporarily save the matrix
        long int tmpMat2[4];
        for (int k = 0; k < 4; ++k)
            tmpMat2[k] = *(mat + k);
        // matrix multiplication with additional element.
        *(mat + 0 * cols + 0) = tmpMat1[0*cols+0] * tmpMat2[0*cols+0] + tmpMat1[0*cols+1] * tmpMat2[1*cols+0];
        *(mat + 0 * cols + 1) = tmpMat1[0*cols+0] * tmpMat2[0*cols+1] + tmpMat1[0*cols+1] * tmpMat2[1*cols+1];
        *(mat + 1 * cols + 0) = tmpMat1[1*cols+0] * tmpMat2[0*cols+0] + tmpMat1[1*cols+1] * tmpMat2[1*cols+0];
        *(mat + 1 * cols + 1) = tmpMat1[1*cols+0] * tmpMat2[0*cols+1] + tmpMat1[1*cols+1] * tmpMat2[1*cols+1];
    }

    return mat;
}
