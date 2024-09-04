/*************************************************************************
	> File Name: head.h
	> Author:Royi
	> Mail:royi990001@gmail.com
	> Created Time: Sat 04 May 2024 05:12:07 PM CST
	> Describe:
 ************************************************************************/
#ifndef _HEAD_H__
#define _HEAD_H__

/* ------------------------------ head.h ----------------------------*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h> 				// va_start, va_end

/* ------------------------------- sys -------------------------------*/
#include <unistd.h>					// nonblock
#include <fcntl.h> 					// nonblock
//#include <pthread.h> 				// <pthread> had been include in thread_pool.h
#include <sys/types.h> 				// sys
#include <sys/socket.h> 			// socket, send, recv...
#include <arpa/inet.h> 				//
#include <signal.h> 				// signal

/* ------------------------------- oth -------------------------------*/

#include "./color.h"
#include "./datatype.h" 			// 设备数据
#include "./client.h" 				// 接收线程

#endif

/* ------------------------------ draw -------------------------------*/
#include <ncurses.h>
#include <locale.h>
#include "./chat_ui.h"


/* ------------------------------- DBG -------------------------------*/ 
#ifdef _D
#define DBG(fmt, args...) printf(fmt, ##args)
#else
#define DBG(fmt, args...)
#endif


/* ------------------------------- log -------------------------------*/
#ifndef _LOG_MESSAGE_H
#define _LOG_MESSAGE_H


#define LOG_LEVEL_INFO 0
#define LOG_LEVEL_WARNING 1
#define LOG_LEVEL_ERROR 2
#define LOG_LEVEL_UNKNOWN 3

#define LOGT_ADD 0
#define LOGT_NEW 1

void log_event(int level, const char *filename, int log_type, const char *format, ...);

#endif
