/*************************************************************************
	> File Name: ../include/server.h
	> Author: 
	> Mail: 
	> Created Time: Thu 15 Aug 2024 03:49:24 PM CST
 ************************************************************************/

#ifndef _SERVER_H
#define _SERVER_H

#include <map>
#include <string>

void signalHandler(int);

void events_handle(int, std::map<std::string, int> &, std::map<int, std::string> &, bool *);

void loginFunction(int, int);

void handle_ctl(int, SmhMsg &, std::map<int, std::string> &);

void HeartSending(std::map<std::string, int> &, std::map<int, std::string> &, bool *);



#endif
