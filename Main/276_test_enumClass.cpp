/*================================================================
*   Copyright (C) 2021 Renleilei. All rights reserved.
*   
*   文件名称：276_test_enumClass.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2021年10月21日
*   描    述：简略测试 C++11中 enum class 的类型转换结果
*   版    本: Version 1.00
*   编译指令: g++ -o main 276_test_enumClass.cpp
================================================================*/

#include <iostream>

using namespace std;

enum class ETest {
    ETest_Val1 = 100,
    ETest_Val2 = 102,
    ETest_Val3 = 103,
    ETest_Val4 = 104
};

int main(int argc, char** argv)
{
    int val1 = static_cast<int>(ETest::ETest_Val1);
    double val2 = static_cast<double>(ETest::ETest_Val2);
    float val3 = static_cast<float>(ETest::ETest_Val3);
    long long val4 = static_cast<long long>(ETest::ETest_Val4);

    int val5 = 199;
    ETest eVal5 = static_cast<ETest>(val5);
    int iVal5 = static_cast<int>(eVal5);

    std::cout << "1, val1: " << val1 << std::endl;
    std::cout << "2, val2: " << val2 << std::endl;
    std::cout << "3, val3: " << val3 << std::endl;
    std::cout << "4, val4: " << val4 << std::endl;
    std::cout << "5, ival5: " << iVal5 << std::endl;

    return 0;
}
