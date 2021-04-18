

/*
实现函数 atoi 。函数的功能为将字符串转化为整数
提示：仔细思考所有可能的输入情况。这个问题没有给出输入的限制，你需要自己考虑所有可能的情况。

示例1
输入 "123" 返回值 123
*/

#include <iostream>
#include <cstring>

using namespace std;

int my_atoi(const char* src) {
    int idx = 0;    // 索引
    int sign = 1;   // 乘数
    int retVal = 0; // 返回值
    // 1, 考虑空字符串
    if (src == nullptr) return 0;
    // 2, 处理前置的0
    while (src[idx] == '0') {
        idx++;
    }
    // 3, 记录正负
    if (src[idx] == '-') {
        sign = -1;
        idx++;
    } else if (src[idx] == '+') {
        idx++;
    }

    for (; idx < static_cast<int>(strlen(src)); idx++) {
        // 4, 处理非法输入
        if (src[idx] > '9') break;
        // 5, 处理溢出
        if (retVal > INT32_MAX / 10 || (retVal == INT32_MAX / 10 && INT32_MAX % 10 < src[idx] - '0')) {
            return sign == 1 ? INT32_MAX : INT32_MIN;
        }

        retVal = retVal * 10 + (src[idx] - '0');
    }
    
    return retVal * sign;
}

int main() {

    // 测试
    const char* strSrc1 = "-13100012";
    int ret1 = my_atoi(strSrc1);
    std::cout << "[1] \""<< strSrc1 << "\" is : " << ret1 << std::endl;

    const char* strSrc2 = "+2147483647";
    int ret2 = my_atoi(strSrc2);
    std::cout << "[2] \""<< strSrc2 << "\" is : " << ret2 << std::endl;

    const char* strSrc3 = "   -42";
    int ret3 = my_atoi(strSrc3);
    std::cout << "[3] \""<< strSrc3 << "\" is : " << ret3 << std::endl;

    const char* strSrc4 = "4193 with words";
    int ret4 = my_atoi(strSrc4);
    std::cout << "[4] \""<< strSrc4 << "\" is : " << ret4 << std::endl;

    const char* strSrc5 = "words and 987";
    int ret5 = my_atoi(strSrc5);
    std::cout << "[5] \""<< strSrc5 << "\" is : " << ret5 << std::endl;

    const char* strSrc6 = " ";
    int ret6 = my_atoi(strSrc6);
    std::cout << "[6] \""<< strSrc6 << "\" is : " << ret6 << std::endl;

    const char* strSrc7 = "-91283472332";
    int ret7 = my_atoi(strSrc7);
    std::cout << "[7] \""<< strSrc7 << "\" is : " << ret7 << std::endl;

    const char* strSrc8 = "10000000000000000000000000000000000000000000000000000000000000000522545459";
    int ret8 = my_atoi(strSrc8);
    std::cout << "[8] \""<< strSrc8 << "\" is : " << ret8 << std::endl;

    const char* strSrc9 = "00000000000000000000000000000000000000000000000000000000000000000522545459";
    int ret9 = my_atoi(strSrc9);
    std::cout << "[9] \""<< strSrc9 << "\" is : " << ret9 << std::endl;

    return 0;
}