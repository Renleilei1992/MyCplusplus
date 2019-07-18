/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：145_socket_server.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年07月17日
*   描    述：
*   版    本: Version 1.00
* 	参考文献: [C语言中文网很详尽的解释](http://c.biancheng.net/view/2128.html)
================================================================*/

#include <sys/types.h>
#include <sys/socket.h>
#include <cstdio>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <cstdlib>
#include <fcntl.h>
#include <sys/shm.h>

#define MYPORT 		8887
#define QUEUE 		20
#define BUFFER_SIZE 1024

int main()
{
	// 定义sockfd AF_INET(IPv4) AF_INET6(IPv6) AF_LOCAL(UNIX协议) AF_ROUTE(路由套接字) AF_KEY(密钥套接字)
	// SOCK_STREAM(字节流套接字) SOCK_DGRM
	int server_sockfd = socket(AF_INET, SOCK_STREAM, 0);

	// 定义sockaddr_in
	struct sockaddr_in server_sockaddr;
	memset(&server_sockaddr, 0, sizeof(server_sockaddr));	// 每个字节都用0填充
	server_sockaddr.sin_family = AF_INET;					// 使用IPv4地址
	server_sockaddr.sin_port = htons(MYPORT);				// 端口号
	server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);	// 具体的IP地址

	// bind: 成功返回0， 出错返回 -1
	if (bind(server_sockfd, (struct sockaddr *)&server_sockaddr, sizeof(server_sockaddr)) == -1) {
		perror("bind error");
		exit(EXIT_FAILURE);
	}
	
	// listen: 成功返回0, 出错返回 -1
	printf("监听 %d 端口...\n", MYPORT);
	if (listen(server_sockfd, QUEUE) == -1) {
		perror("listen error");
		exit(EXIT_FAILURE);
	}

	// 客户端套接字
	char buffer[BUFFER_SIZE];
	struct sockaddr_in client_addr;
	socklen_t length = sizeof(client_addr);

	// accept: 等待客户端链接,,,
	printf("等待客户端连接...\n");
	int conn = accept(server_sockfd, (struct sockaddr*)&client_addr, &length);
	if (conn < 0) {
		perror("connect error");
		exit(EXIT_FAILURE);
	}

	printf("客户端成功连接: conn = [%d]\n", conn);
	char str[] = "hello client!!";
	write(conn, str, sizeof(str));		// 向客户端发送了一个字符串过去

	// 循环
	while (1) {
		memset(buffer, 0, sizeof(buffer));
		long len = recv(conn, buffer, sizeof(buffer), 0);
		
		// 客户端发送exit或者异常结束时, 退出
		if (strcmp(buffer, "exit\n") == 0 || len <= 0) {
			printf("something error happened!\n");
			break;
		}

		printf("来自客户端的数据: %s\n", buffer);
//		fwrite(buffer, len, 1, stdout);
//		send(conn, buffer, len, 0);
		char strSend[] = "recv the message from client!!";
		printf("发送给客户端的数据: %s \n", strSend);

		// 休息1s后向客户端回复消息
		sleep(1);
		write(conn, strSend, sizeof(strSend));
//		fwrite(buffer, len, 1, stdout);
	}

	printf("begin close...........\n");
	close(conn);
	close(server_sockfd);
	
	return 0;
}
