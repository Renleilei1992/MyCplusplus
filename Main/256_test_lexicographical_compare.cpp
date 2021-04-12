/*================================================================
*   Copyright (C) 2021 Renleilei. All rights reserved.
*   
*   文件名称：256_test_lexicographical_compare.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2021年04月12日
*   描    述：判断版本号的大小
*   版    本: Version 1.00
*   编译指令：g++ -o main 256_test_lexicographical_compare.cpp -std=c++11
================================================================*/
#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <iterator>
#include <sstream>
using namespace std;

// 对比两个版本号, 例如: 1.3.18.2 与 1.4.0.1, 后者版本号更新
// 返回值：
//       -1： versionA < versionB
//        0:  versionA == versionB
//        1:  versionA > versionB
int compareVersion(const std::string& versionA, const std::string& versionB);

// 版本对比单元测试.
void q_unittest();

int main()
{
	// bool值按照 true 和 false 输出.
    //std::cout << std::boolalpha;

    std::vector<string> phrase1{ "the", "tigers", "of", "wrath" };
    std::vector<string> phrase2{ "the", "horses", "of", "instruction" };
    auto less = std::lexicographical_compare(std::begin(phrase1), std::end(phrase1), std::begin(phrase2), std::end(phrase2));
    std::copy(std::begin(phrase1), std::end(phrase1), std::ostream_iterator<string>{std::cout, " "});
    std::cout << (less ? "are" : "are not") << " less than ";
    std::copy(std::begin(phrase2), std::end(phrase2), std::ostream_iterator<string>{std::cout, " "});
    std::cout << std::endl;

    std::array<int, 4> array1{ 1, 3, 19, 2 };
    std::array<int, 4> array2{ 1, 3, 20, 1 };
    auto bLess1 = std::lexicographical_compare(std::begin(array1), std::end(array1), std::begin(array2), std::end(array2));
    std::copy(std::begin(array1), std::end(array1), std::ostream_iterator<int>{std::cout, " "});
    std::cout << ((bLess1) ? " < " : " > ");
    std::copy(std::begin(array2), std::end(array2), std::ostream_iterator<int>{std::cout, " "});
    std::cout << std::endl;

    std::string v1 = "1.3.18.2";
    std::string v2 = "1.4.0.1";
    compareVersion(v1, v2);

    q_unittest();
    return 0;
}

int compareVersion(const std::string& versionA, const std::string& versionB)
{
    if (versionA == versionB) {
        return 0;
    }
    
    auto parseVersion = [&](int resultArr[], const std::string& strVersion) -> void {
        std::istringstream parser(strVersion);
        parser >> resultArr[0];
        for (int i = 1; i < 4; i++) {
            parser.get();
            parser >> resultArr[i];
        }
    };

    std::string strA = versionA;
    std::string strB = versionB;

    int arrayA[4]{}, arrayB[4]{};
    parseVersion(arrayA, strA);
    parseVersion(arrayB, strB);

    // arrayA 按字典序 小于 arrayB 会返回 true
    bool ret = std::lexicographical_compare(std::begin(arrayA), std::end(arrayA), std::begin(arrayB), std::end(arrayB));

    // print array
    // std::cout << __func__ << ":: ";
    // for (int i = 0; i < 4; i++) {
    //     std::cout << "A: " << arrayA[i] << " B: " << arrayB[i] << " ";
    // }
    // std::cout << std::endl;
    
    
    // print log
    std::cout << __func__ << ":: versionA[" << versionA << "] " << (ret ? "<" : ">") << " versionB[" << versionB << "]" << std::endl;

    int result = ret ? -1 : 1;
    return result;
}

void q_unittest()
{
    std::string version1 = "1.3.19.2";
    std::string version2 = "1.4.0.0";
    std::string version3 = "0.1.999.2";
    std::string version4 = "2.0.1.0";
    std::string version5 = "1.9.2.1";

    compareVersion(version1, version1);
    compareVersion(version1, version2);
    compareVersion(version1, version3);
    compareVersion(version1, version4);
    compareVersion(version1, version5);
    compareVersion(version2, version1);
    compareVersion(version2, version2);
    compareVersion(version2, version3);
    compareVersion(version2, version4);
    compareVersion(version2, version5);
    compareVersion(version3, version1);
    compareVersion(version3, version2);
    compareVersion(version3, version3);
    compareVersion(version3, version4);
    compareVersion(version3, version5);
    compareVersion(version4, version1);
    compareVersion(version4, version2);
    compareVersion(version4, version3);
    compareVersion(version4, version4);
    compareVersion(version4, version5);
    compareVersion(version5, version1);
    compareVersion(version5, version2);
    compareVersion(version5, version3);
    compareVersion(version5, version4);
    compareVersion(version5, version5);
}
