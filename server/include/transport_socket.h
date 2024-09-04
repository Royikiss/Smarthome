/*************************************************************************
	> File Name: ../include/transport_socket.h
	> Author: 
	> Mail: 
	> Created Time: Wed 14 Aug 2024 04:49:13 PM CST
 ************************************************************************/

#ifndef _TRANSPORT_SOCKET_H
#define _TRANSPORT_SOCKET_H

struct UsrMsg {
    int fd;
    char username[20];
};

void send_UsrMsg(int socket, const UsrMsg &usr_msg);

int recv_UsrMsg(int socket, UsrMsg &usr_msg);

#endif
