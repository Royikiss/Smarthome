/*************************************************************************
	> File Name: net.h
	> Author:Royi 
	> Mail:royi990001@gmail.com 
	> Created Time: Tue 07 May 2024 08:33:54 PM CST
	> Describe: 
 ************************************************************************/
#ifndef _NET_H__
#define _NET_H__

int socket_create(int port);

int socket_connect(const char *ip, int port);

#endif

