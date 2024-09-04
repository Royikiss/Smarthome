/*************************************************************************
	> File Name: ../include/server.h
	> Author: 
	> Mail: 
	> Created Time: Thu 15 Aug 2024 03:49:24 PM CST
 ************************************************************************/

#ifndef _SERVER_H
#define _SERVER_H

void signalHandler(int signum);

void events_handle(int sockfd, std::map<std::string, int> &u2f, std::map<int, std::string> &f2u);

void loginFunction(int bridge, int client_fd);


#endif
