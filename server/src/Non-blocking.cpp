/*************************************************************************
	> File Name: Non-blocking.c
	> Author:Royi 
	> Mail:royi990001@gmail.com 
	> Created Time: Tue 07 May 2024 10:53:49 AM CST
	> Describe: 
 ************************************************************************/

#include "../include/head.h"
#include "../include/Non-blocking.h"

int make_nonblock(int fd) {
	int flag;
	if ((flag = fcntl(fd, F_GETFL)) < 0) {
		return -1;
	}
	flag |= O_NONBLOCK;
	return fcntl(fd, F_SETFL, flag);
}

int make_block(int fd) {
	int flag;
	if ((flag = fcntl(fd, F_GETFL)) < 0) {
		return -1;
	}
	flag &= ~O_NONBLOCK;
	return fcntl(fd, F_SETFL, flag);
}
