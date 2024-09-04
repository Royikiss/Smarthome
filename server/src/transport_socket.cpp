/*************************************************************************
	> File Name: ../src/transport_socket.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 14 Aug 2024 04:50:45 PM CST
 ************************************************************************/

#include "../include/head.h"
#include "../include/transport_socket.h"

void send_fd(int socket, const UsrMsg &usr_msg) {
    msghdr message;
    iovec iov[1];
    cmsghdr *ctrl_msg = NULL;
    char buf[CMSG_SPACE(sizeof(int))];
    char dummy_data[1] = {0};

    // 使用 dummy_data 作为发送的数据，同时附带 control message
    iov[0].iov_base = (void*)&usr_msg;
    iov[0].iov_len = sizeof(usr_msg);

    message.msg_name = NULL;
    message.msg_namelen = 0;
    message.msg_iov = iov;
    message.msg_iovlen = 1;
    message.msg_control = buf;
    message.msg_controllen = sizeof(buf);

    ctrl_msg = CMSG_FIRSTHDR(&message);
    ctrl_msg->cmsg_level = SOL_SOCKET;
    ctrl_msg->cmsg_type = SCM_RIGHTS;
    ctrl_msg->cmsg_len = CMSG_LEN(sizeof(int));

    int *fdptr = (int *)CMSG_DATA(ctrl_msg);
    *fdptr = usr_msg.fd;

    if (sendmsg(socket, &message, 0) < 0) {
        perror("Failed to send message");
        return;
    }
}

int recv_fd(int socket, UsrMsg &usr_msg) {
    msghdr message;
    iovec iov[1];
    cmsghdr *ctrl_msg = NULL;
    char buf[CMSG_SPACE(sizeof(int))];
    char dummy_data[sizeof(UsrMsg)];

    iov[0].iov_base = dummy_data;
    iov[0].iov_len = sizeof(dummy_data);

    message.msg_name = NULL;
    message.msg_namelen = 0;
    message.msg_iov = iov;
    message.msg_iovlen = 1;
    message.msg_control = buf;
    message.msg_controllen = sizeof(buf);

    if (recvmsg(socket, &message, 0) < 0) {
        perror("Failed to receive message");
        return -1;
    }

    // 从消息中提取 usr_msg
    memcpy(&usr_msg, dummy_data, sizeof(UsrMsg));

    ctrl_msg = CMSG_FIRSTHDR(&message);
    if (ctrl_msg && ctrl_msg->cmsg_level == SOL_SOCKET && ctrl_msg->cmsg_type == SCM_RIGHTS) {
        usr_msg.fd = *((int *)CMSG_DATA(ctrl_msg));
        return usr_msg.fd;
    }
    return -1;
}

