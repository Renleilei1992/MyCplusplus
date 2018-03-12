/*================================================================
*   Copyright (C) 2018 Renleilei. All rights reserved.
*   
*   文件名称：034_Big_Little_endian.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2018年03月12日
*   描    述：
*   版    本: Version 1.00
*   编译命令: 
================================================================*/

#include <stdio.h>
#include <stdlib.h>
typedef unsigned char byte;
 
// 转换char（视为整数类型）为16进制字符串
void ChtoHex(byte Val, char* dest)
{
    // 辗转相除法，倒序看得到结果
 
    byte tmp = Val % 16;
    if (tmp >= 0 && tmp <= 9)
    {
        dest[1] = '0' + tmp;
    }
    else if (tmp >= 10 && tmp <= 15)
    {
        dest[1] = 'A' + tmp - 10;
    }
 
    tmp = (Val/16) % 16;
    if (tmp >= 0 && tmp <= 9)
    {
        dest[0] = '0' + tmp;
    }
    else if (tmp >= 10 && tmp <= 15)
    {
        dest[0] = 'A' + tmp - 10;
    }
 
    // 设置\0
    dest[2] = '\0';
}
 
// 主函数
int main()
{
    int u = 367328153; // 原始数据，8位16进制为15 E4 FB 99
    byte a, b, c, d;   // u从低地址到高地址的四个字节
    // a~d对应的16进制字符串，预留3个字符
    char Sa[3], Sb[3], Sc[3], Sd[3]; 
 
    byte* k = (byte*)&u;
    a = k[0];
    b = k[1];
    c = k[2];
    d = k[3];
 
    // 转成16进制字符串
    ChtoHex(a, Sa);
    ChtoHex(b, Sb);
    ChtoHex(c, Sc);
    ChtoHex(d, Sd);
 
    printf("%s %s %s %s\n", Sa, Sb, Sc, Sd);
 
//    scanf_s("%d", &a);

    return 1;
}
