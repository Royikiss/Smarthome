/*************************************************************************
	> File Name: client.c
	> Author:Royi 
	> Mail:royi990001@gmail.com 
	> Created Time: Thu 09 May 2024 01:28:24 PM CST
	> Describe: 
 ************************************************************************/

#include "../include/head.h"
#include "../include/common.h"

extern int sockfd;
extern WINDOW *message_sub;
extern struct User usrinfo;
extern struct SmhSmg chat_msg;

void *client_recv(void *arg) {
    struct SmhMsg msg_pre, msg_tmp, msg, smsg;
	size_t msg_size = sizeof(msg);
	int offset = 0, recv_size = 0, send_size;

	bzero(&msg_pre, sizeof(msg_pre));
	bzero(&msg_tmp, sizeof(msg_tmp));
	bzero(&msg, sizeof(msg));
	bzero(&smsg, sizeof(smsg));
	
	DBG(GREEN"thread : client_recv init OK!\n"NONE);

	while (1) {
		//DBG(GREEN"Start recv a new pack!\n"NONE);
		bzero(&msg_tmp, sizeof(msg_tmp));
		if (offset) {
			//DBG(YELLOW"Last pack is '拆包'\n"NONE);
			memcpy(&msg, &msg_pre, offset);
		}
		while ((recv_size = recv(sockfd, (void *)&msg_tmp, msg_size, 0)) > 0) {
			//DBG(GREEN"Recived a package!\n"NONE);
			if (offset + recv_size == msg_size) {
				DBG(PINK"[整包]"NONE);
				memcpy((char *)&msg + offset, (char *)&msg_tmp, recv_size);
				offset = 0;
				break;
			} else if (offset + recv_size < msg_size) {
				DBG(PINK"[拆包]"NONE);
				memcpy((char *)&msg + offset, (char *)&msg_tmp, recv_size);
				offset += recv_size;
			} else if (offset + recv_size > msg_size) {
				DBG(PINK"[粘包]"NONE);
				int wait = msg_size - offset;
				memcpy((char *)&msg + offset, (char *)&msg_tmp, wait);
				offset = recv_size - wait;
				memcpy((char *)&msg_pre, (char *)&msg_tmp + wait, offset);
				break;
			}
		}

		if (recv_size <= 0) break;
		strcpy(usrinfo.name, msg.name);
		if (msg.type & SMH_HEART) {
			bzero(&smsg, sizeof(smsg));
			smsg.type = SMH_ACK;
			if((send_size = send(sockfd, (void *)&smsg, sizeof(smsg), 0)) < 0) {
				DBG(RED"Heart respond faild!\n"NONE);
			} else {
				DBG(GREEN"Heart respond success!\n"NONE);
			}
	    } else if (msg.type & SMH_MSG) {
	        show_message(message_sub, &usrinfo, (char *)msg.msg, 0);
	    } else if (msg.type & SMH_WALL) {
	        show_message(message_sub, &usrinfo, (char *)msg.msg, 0);
	    } else if (msg.type & SMH_FIN) {
			DBG(GREEN"[服务器停止]: %s\n"NONE, msg.msg);
	        show_message(message_sub, &usrinfo, "服务器正要停止。\n", 0);
	        close(sockfd);
	        exit(0);
	    } else if (msg.type & SMH_CTL){
	        show_message(message_sub, &usrinfo, msg.msg, 0);
	    } else {
			DBG(RED"Msg Unsupport!\n"NONE);
		}
		bzero(&msg, sizeof(msg));
	}
}

void logout(int signum) {
	struct SmhMsg msg;
	memset(&msg, 0, sizeof(msg));
	msg.type = SMH_FIN;
	if ((send(sockfd, (void *)&msg, sizeof(msg), 0)) < 0) {
		DBG(RED"send 'FIN' faild!\n");
	}
	close(sockfd);
	DBG(BLUE"Bye~\n"NONE);
	sleep(1);
	exit(0);
}
