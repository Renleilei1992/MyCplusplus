/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：091_getHostDns.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年03月04日
*   描    述：
*   版    本: Version 1.00
================================================================*/

#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <typeinfo>
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    struct hostent *ht=NULL;

    /* 查询的主机域名 */
    char host[]="www.baidu.com";

 #if 1
    struct hostent *ht1=NULL, *ht2=NULL;
    char host1[]="www.baidu.com";
    /* 查询主机www.sina.com.cn */
    ht1 = gethostbyname(host);
    ht2 = gethostbyname(host1);//函数的不可重入性，前者结果已经被覆盖
    int j = 0;

 #else
    struct in_addr in;
    in.s_addr = inet_addr("60.215.128.140");
    ht = gethostbyaddr(&in, sizeof(in), AF_INET);
 #endif
	for(j = 0;j<2;j++){
    	if(j == 0)
        ht = ht1;
    	else
        ht = ht2;

    	printf("----------------------\n");

    	if(ht){
        	int i = 0;
        	printf("get the host:%s addr\n",host);  /* 原始域名 */
        	printf("name:%s\n",ht->h_name);         /* 名称 */

        	/*协议族AF_INET为IPv4或者AF_INET6为IPv6*/
       		printf("type:%s\n",ht->h_addrtype==AF_INET?"AF_INET":"AF_INET6");

        	/* IP地址的长度 */
        	printf("legnth:%d\n",ht->h_length); 
        	/* 打印IP地址 */
			printf("IP: %s\n", inet_ntoa(*(struct in_addr *)*ht->h_addr_list));
			printf("IP: %u.%u.%u.%u\n", ((*(struct in_addr *)*ht->h_addr_list).s_addr) & 0x000000FF, ((*(struct in_addr *)*ht->h_addr_list).s_addr >> 8) & 0x000000FF, ((*(struct in_addr *)*ht->h_addr_list).s_addr >> 16) & 0x000000FF, ((*(struct in_addr *)*ht->h_addr_list).s_addr >> 24) & 0x000000FF);

        	for(i=0;;i++){
            	if(ht->h_addr_list[i] != NULL){/* 不是IP地址数组的结尾 */
                	//printf("IP:%s\n",inet_ntoa((unsigned int*)ht->h_addr_list[i])); /*打印IP地址*/
                	//printf("IP:%s\n",(unsigned int*)ht->h_addr_list[i]); /*打印IP地址*/
                	//printf("IP:%s\n",inet_ntoa(*(struct in_addr *)*ht->h_addr_list[i])); /*打印IP地址*/
					//printf("IP:%d\n",ntohs(ht->h_addr_list[0][i]));
					//std::cout << "ht->h_addr_list[%d]'s type : " << typeid(ht->h_addr_list[i]).name() << endl;
					//std::cout << "ht->h_addr_list[0][i]'s type : " << typeid(ht->h_addr_list[0][1]).name() << endl;
					//printf("====> %u\n", ht->h_addr_list[0][1].S_addr);
					//printf("get in, ht->h_addr_list[%d] is not NULL!\n", i);
					//printf("IP:%s\n",inet_ntoa(ht->h_addr_list[0][i]));
					std::cout << "  IP: " << inet_ntoa(*(in_addr *)ht->h_addr_list[i]) << endl;
            	}else{/*达到结尾*/
                	break;  /*退出for循环*/
            	}
        	}

			//int p = 10;
			//char cp = 'e';
			//std::cout << "p type name: " << typeid(p).name() << "cp type name: " << typeid(cp).name() << endl;

        	/* 打印域名地址 */
        	for(i=0;;i++){/*循环*/
            	if(ht->h_aliases[i] != NULL){/* 没有到达域名数组的结尾 */
                	printf("alias %d:%s\n",i,ht->h_aliases[i]); /* 打印域名 */
            	}   else{/*结尾*/
                	break;  /*退出循环*/
            	}
        	}
    	}   
}
    return 0;
}
