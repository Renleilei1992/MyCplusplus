/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：092_inet_ntoa.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年03月04日
*   描    述：
*   版    本: Version 1.00
================================================================*/

#define _BSD_SOURCE
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    struct in_addr addr;

    if (argc != 2) {
      fprintf(stderr, "%s <dotted-address>\n", argv[0]);
      exit(EXIT_FAILURE);
    }

    if (inet_aton(argv[1], &addr) == 0) {
      fprintf(stderr, "Invalid address\n");
      exit(EXIT_FAILURE);
    }

//	printf("old: %s\n", addr);   // will Segmentation falut
    printf("%s\n", inet_ntoa(addr));
    exit(EXIT_SUCCESS);
}

