/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：138_pi.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年05月23日
*   描    述：显示圆周率pi的n位小数
*   版    本: Version 1.00
*	参考文献: https://en.cppreference.com/w/cpp/io/manip/setprecision   // std::setprecision
================================================================*/

#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>

using namespace std;

int main()
{
    const long double pi = std::acos(-1.L);
    std::cout << "default precision (6): " << pi << '\n'
              << "std::setprecision(10): " << std::setprecision(10) << pi << '\n'
              << "max precision:         "
              << std::setprecision(std::numeric_limits<long double>::digits10 + 1)
              << pi << '\n';
}
