/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：146_socket_client.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年07月17日
*   描    述：
*   版    本: Version 1.00
*	参考文献: [C语言中文网关于 socket编程的文章, 很详尽](http://c.biancheng.net/view/2128.html)
================================================================*/

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main()
{
	// 创建套接字
	int sock = socket(AF_INET, SOCK_STREAM, 0);

	// 向服务器(特定的IP和端口) 发起请求
	struct sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr));	// 每个字节都用0填充
	server_addr.sin_family = AF_INET;				// 使用IPv4地址
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");	// 具体的IP地址
	server_addr.sin_port = htons(8887);				// 端口
	connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr));

	// 读取服务器传回的数据
	char buffer[40];
	read(sock, buffer, sizeof(buffer) - 1);

	printf("Message from server: %s\n", buffer);

	char str[] = "hello server, I recv your message!!";
	write(sock, str, sizeof(str));

	// 创建一个循环用于接收服务端传回的数据
	int i = 0;
	while (i <= 100) {
		memset(buffer, 0, sizeof(buffer));
        long len = recv(sock, buffer, sizeof(buffer), 0);

		// 服务端发送exit或者异常结束时, 退出
        if (strcmp(buffer, "exit\n") == 0 || len <= 0) {
            printf("something error happened!\n");
            break;
        }

		// 打印服务端发过来的消息
		printf("来自服务端的第[%d]次数据: %s\n", i, buffer);

        char strSend[] = "recv the message from server client!!";
        printf("发送给服务端的数据: %s \n", strSend);
        write(sock, strSend, sizeof(strSend));
		
		i++;
	}

	sleep(3);

	// 关闭套接字
	close(sock);

	return 0;
}
