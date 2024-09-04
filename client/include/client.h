/*************************************************************************
	> File Name: client.h
	> Author:Royi 
	> Mail:royi990001@gmail.com 
	> Created Time: Thu 09 May 2024 01:25:30 PM CST
	> Describe: 
 ************************************************************************/
#ifndef _CLIENT_RECV_H__
#define _CLIENT_RECV_H__

#include <pthread.h>

// 接收信息函数
void *client_recv(void *arg);

// 登出函数
void logout(int signum);

#endif