/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：147_socket_uv_server.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年07月18日
*   描    述：
*   版    本: Version 1.00
*	编译指令: g++ -o main 147_socket_uv_server.cpp -g -Wall -luv ../libs/libuv.a -std=c++11
*	参考文献: [知乎链接](https://zhuanlan.zhihu.com/p/50497450)
================================================================*/

// just add for c++
#include <iostream>
using namespace std;

// ----
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/uv.h"

#define DEFAULT_PORT 			8887
#define DEFAULT_BACKLOG 		128
#define DEFAULT_BUFFER_SIZE		1024*1024


// for log: 打印出函数名
static std::string _CutParenthesesNTail(std::string&& prettyFuncon)
{
    auto pos = prettyFuncon.find('(');
    if(pos!=std::string::npos)
        prettyFuncon.erase(prettyFuncon.begin()+pos, prettyFuncon.end());

    return std::move(prettyFuncon);
}
#define __STR_FUNCTION__ _CutParenthesesNTail(std::string(__PRETTY_FUNCTION__))

uv_loop_t *loop;
struct sockaddr_in addr;

typedef struct {
    uv_write_t req;
    uv_buf_t buf;
} write_req_t;

void free_write_req(uv_write_t *req) {
    write_req_t *wr = (write_req_t*) req;
    free(wr->buf.base);
    free(wr);
}

void alloc_buffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf) {
    buf->base = (char*) malloc(suggested_size);
    buf->len = suggested_size;
}

void on_close(uv_handle_t* handle) {
    free(handle);
}

void echo_write(uv_write_t *req, int status) {
	cout << __STR_FUNCTION__ << "-----------> be called!! status: " << status << endl;
    if (status) {
        fprintf(stderr, "Write error %s\n", uv_strerror(status));
    }
    free_write_req(req);
}

void echo_read(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf) {
//	cout << __STR_FUNCTION__ << "-----------> be called!! nread: " << nread << endl;
    if (nread > 0) {
        write_req_t *req = (write_req_t*)malloc(sizeof(write_req_t));
        req->buf = uv_buf_init(buf->base, nread);

		// new add
		if (buf != nullptr) {
			cout << __STR_FUNCTION__ << "message from client. buff base: [" << buf->base << "]" << endl;
		}

		char tempStr[] = "=======> auto reply from Server!!!!!!";
		memcpy(buf->base, tempStr, sizeof(tempStr));
        //fwrite(buf->base, 30, 1, stdout);
        uv_write((uv_write_t*)req, client, &req->buf, 1, echo_write);
        return;
    }
    if (nread < 0) {
        if (nread != UV_EOF)
            fprintf(stderr, "Read error %s\n", uv_err_name(nread));
        uv_close((uv_handle_t*) client, on_close);
    }

    free(buf->base);
}

void on_new_connection(uv_stream_t *server, int status) {
    if (status < 0) {
        fprintf(stderr, "New connection error %s\n", uv_strerror(status));
        // error!
        return;
    }

	cout << __STR_FUNCTION__ << "----------> new connection build! status: " << status << endl;	

    uv_tcp_t *client = (uv_tcp_t*)malloc(sizeof(uv_tcp_t));
    uv_tcp_init(loop, client);
    if (uv_accept(server, (uv_stream_t*)client) == 0) {
		cout << "uv_accept success, uv_read_start begin..." << endl;
        uv_read_start((uv_stream_t*)client, alloc_buffer, echo_read);

		cout << "uv_accept success, uv_write_start begin..." << endl;
        write_req_t *req = (write_req_t*)malloc(sizeof(write_req_t));
        req->buf = uv_buf_init((char*)malloc(DEFAULT_BUFFER_SIZE), DEFAULT_BUFFER_SIZE);
		char tempStr[] = "Server Return String!!";
		memcpy(req->buf.base, tempStr, sizeof(tempStr));
        //fwrite(req->buf.base, 30, 1, stdout);
        uv_write((uv_write_t*)req, (uv_stream_t *)client, &req->buf, 1, echo_write);
    }
    else {
		cout << "uv_close begin..." << endl;
        uv_close((uv_handle_t*) client, on_close);
    }
}

int main() {
    loop = uv_default_loop();

    uv_tcp_t server;
    uv_tcp_init(loop, &server);

    uv_ip4_addr("127.0.0.1", DEFAULT_PORT, &addr);

    uv_tcp_bind(&server, (const struct sockaddr*)&addr, 0);
    int r = uv_listen((uv_stream_t*) &server, DEFAULT_BACKLOG, on_new_connection);
    if (r) {
        fprintf(stderr, "Listen error %s\n", uv_strerror(r));
        return 1;
    }
    return uv_run(loop, UV_RUN_DEFAULT);
}
