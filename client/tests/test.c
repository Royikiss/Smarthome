/*************************************************************************
	> File Name: test.c
	> Author:Royi 
	> Mail:royi990001@gmail.com 
	> Created Time: Mon 06 May 2024 09:53:21 PM CST
	> Describe: 
 ************************************************************************/

#include "../include/head.h"
#include "../include/common.h"
#include "../include/net.h"
#include "../include/Non-blocking.h"
#include "../include/User.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        DBG(RED"argc = %d\n"NONE, argc);
        fprintf(stderr, "Usage: %s ip port\n", argv[0]);
        return 1;
    }
    int sockfd;
    if ((sockfd = socket_connect(argv[1], atoi(argv[2]))) < 0) {
        DBG(RED"Connect failed ! \n"NONE);
        return 1;
    }
    
    char buff[512];
    ssize_t size;
    struct UserInfo user;
    strcpy(user.name, "贾泽同");
    strcpy(user.phone, "18763919116");

    while(1) {
        size = recv(sockfd, buff, 511, 0);
        if (size < 0) {
            perror("recv");
            exit(1);
        } else if (size == 0) {
            DBG(GREEN"server end !\n"NONE);
            return 0;
        } else {
            switch(buff[0]) {
                case 1: {
                    DBG(GREEN"send a phone!\n"NONE);
                    size = send(sockfd, user.phone, sizeof(user.phone), 0);
                    DBG(GREEN"send %d bytes.\n"NONE, size);
                    break;
                }
                case 2: {
                    DBG(GREEN"send a name!\n"NONE);
                    size = send(sockfd, user.name, sizeof(user.name), 0);
                    DBG(GREEN"send %d bytes.\n"NONE, size);
                    break;
                }
                case 3: {
                    DBG(GREEN"send a user!\n"NONE);
                    size = send(sockfd, &user, sizeof(user), 0);
                    DBG(GREEN"send %d bytes.\n"NONE, size);
                    break;
                }
                case 4: {
                    close(sockfd);
                    DBG(GREEN"close fd!\n"NONE);
                    return 0;
                }
                default : {
                    DBG("Recv other message: %s\n", buff);
                }
            }
        }
    }
    return 0;
}
