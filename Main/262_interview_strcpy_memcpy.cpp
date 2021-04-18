
/* 实现strcpy 和 memcpy */

#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

// 实现strcpy
char* strcpy_v1(char* strDest, const char* strSrc)
{
    // v1 版本不能处理内存重叠的场景.
    if (strDest == nullptr || strSrc == nullptr) {
        return nullptr;
    }

    char* address = strDest;
    while (*strSrc != '\0') {
        *strDest = *strSrc;
        strDest++;
        strSrc++;
    }
    
    return address;
}

// 实现memcpy
void* memcpy_v1(void *pvTo, void *pvFrom, size_t size)
{
    // v1 版本不处理内存重叠的场景
    if (pvTo == nullptr || pvFrom == nullptr) {
        return nullptr;
    }

    char* pbTo = (char*)pvTo;   // memcpy的size是byte字节
    char* pbFrom = (char*)pvFrom;

    while (size-- > 0)
    {
        *pbTo++ = *pbFrom++;
    }

    return pvTo;
}

char* memcpy_v2(char *pvTo, char *pvFrom, size_t size)
{
    if (pvTo == nullptr || pvFrom == nullptr) {
        return nullptr;
    }
    
    char* ret = pvTo;

    if (pvTo >= pvFrom && pvTo <= (pvFrom + size - 1)) {
        /* 内存重叠 从高地址开始复制 */
        pvTo = pvTo + size - 1;
        pvFrom = pvFrom + size - 1;

        while (size--) {
            *pvTo-- = *pvFrom--;
        }
    } else {
        while (size--) {
            *pvTo++ = *pvFrom++;
        }
    }
    return ret;
}

int main() {

    char s1[20] = "hello world!";
    strcpy_v1(s1, s1+1);
    std::cout << "[1] s1: " << std::string(s1) << std::endl;

    // char* str1 = "Hello";
    // char* str2 = new char[10];
    // char* str3 = memcpy_v1(str2, str1, 5);
    char strSrc[30] = "Hello memcpy!";
    char strDest[30];
    memcpy_v2(strDest, strSrc, 30);
    std::cout << "[2] strDest: " << std::string(strDest) << std::endl; 

    return 0;
}