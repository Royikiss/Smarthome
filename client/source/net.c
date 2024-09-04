/*************************************************************************
	> File Name: net.c
	> Author:Royi 
	> Mail:royi990001@gmail.com 
	> Created Time: Tue 07 May 2024 08:34:08 PM CST
	> Describe: 
 ************************************************************************/

#include "../include/head.h"
#include "../include/net.h"

int socket_create(int port) {
	int sockfd;
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		return -1;
	}
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = inet_addr("0.0.0.0");

	int val = 1;

	// 设置地址重用
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(int)) < 0) {
		return -1;
	}

	if (bind(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0) {
		return -1;
	}

	if (listen(sockfd, 10) < 0) {
		return -1;
	}

	return sockfd;
}


// 返回一个从port连接ip的套接字
int socket_connect(const char *ip, int port) {
	int sockfd;
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		return -1;
	}
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = inet_addr(ip);

	if ((connect(sockfd, (struct sockaddr *)&server, sizeof(server))) < 0) {
		return -1;
	}

	return sockfd;
}