/*************************************************************************
	> File Name: head.h
	> Author:Royi 
	> Mail:royi990001@gmail.com 
	> Created Time: Mon 29 Jul 2024 07:01:13 PM CST
	> Describe: 
 ************************************************************************/
#ifndef _HEAD_H__
#define _HEAD_H__

/******************************** IO *************************************/
#include <iostream>
#include <sstream>
#include <algorithm>

/********************************* C *************************************/

#include <cstdio>
#include <cstdlib>
#include <ctype.h>
#include <cmath>

/****************************** unistd ***********************************/
#include <unistd.h>
#include <sys/epoll.h>
#include <sys/wait.h>

#include "./Cgo/Cgo.h"              // Cgo 库,主要是使用线程池
#include "./net.h"                  // 网络通讯函数,套接字的创建与设置
#include "./Non-blocking.h"         // 非阻塞函数
#include "./datatype.h"             // 服务器所需数据结构
#include "./transport_socket.h"     // 父子进程的套接字传递函数
#include "./server.h"

// mysql
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/exception.h>

/******************************* head ***********************************/

#include "./DBG/DBG"                // debug相关内容

#endif
