/*************************************************************************
	> File Name: client_window.c
	> Author:Royi 
	> Mail:royi990001@gmail.com 
	> Created Time: Wed 08 May 2024 06:52:43 PM CST
	> Describe: 
 ************************************************************************/

#include "../include/head.h"
#include "../include/common.h"
#include "../include/net.h"
#include "../include/Non-blocking.h"
#include "../include/User.h"
#include "../include/client.h"
#include "../include/send_chat.h"

int sockfd;
WINDOW *message_win, *message_sub,  *info_win, *input_win, *info_sub;
int message_num = 0;
struct User usrinfo;
struct SmhMsg chat_msg;
char *S_IP;                         // 服务器端IP地址
char *S_PORT;                       // 服务器端端口地址
char *S_NAME;                       // 用户名
char *S_PASSWD;                     // 密码
char _Server_Tmp_[VALUE_SIZE];
char _Server_Value_[VARIABLE_NUM][VALUE_SIZE];

int s_init(struct LogRequest * LogMessage);

int main() {
    struct LogRequest LogReq;                   // 登陆请求信息
    struct LogResponse LogResp;                 // 登陆回应信息
    memset(&LogReq, 0, sizeof(LogReq));

    setlocale(LC_ALL,"");
    #ifndef _D
        init_ui();
    #endif

    // 设定退出信号
    signal(SIGINT, logout);

    // 读取配置文件
    if (s_init(&LogReq) < 0) {
        DBG(RED"Init LogRequest fild!\n"NONE);
        return 1; 
    }
    
    // 发送连接
    if ((sockfd = socket_connect(S_IP, atoi(S_PORT))) < 0) {
        DBG(RED"connect filed!\n"NONE);
        return 1;
    } else {
        DBG(GREEN"connect OK!\n"NONE);
    }

    // 发送登陆信息
    ssize_t size;
    if ((size = send(sockfd, &LogReq, sizeof(LogReq), 0)) < 0) {
        DBG(RED"Send LogReq faild! {$size = %ld}\n"NONE, size);
    }

    // 接受服务器信息
    if ((size = recv(sockfd, &LogResp, sizeof(LogResp), 0)) < 0) {
        DBG(RED"Recv LogResp faild! {$size = %ld}\n"NONE, size);
    } else {
        DBG(GREEN"%s"NONE, LogResp.msg);
    }

    // 创建一个线程去执行信息的接收
    pthread_t recv_tid;
    pthread_create(&recv_tid, NULL, client_recv, NULL);

    //循环输入缓冲区,用作信息的输入输出
    while (1) {
	    int c = getchar();
	    switch (c) {
		    case 13:{
	    		send_chat();            // 如果是回车直接发送
			    break;
		    }
		    default:
			    break;
	    }
	    box(input_win, 0, 0);
	    wrefresh(input_win);
    }

    return 0;
}

/* 初始化 */
int s_init(struct LogRequest * LogMessage) {
    if ((S_IP = get_config_value("../config/configfile", "SERVER_IP")) == NULL) {
        log_event(LOG_LEVEL_ERROR, "../config/log.txt", LOGT_NEW, "SERVER_IP lost!\n");
        return -1;
    } else {
        DBG(BLUE"Get env : ${SERVER_IP} = {%s}\n"NONE, S_IP);
    }

    if ((S_PORT = get_config_value("../config/configfile", "SERVER_PORT")) == NULL) {
        log_event(LOG_LEVEL_ERROR, "../config/log.txt", LOGT_NEW, "SERVER_PORT lost!\n");
        return -1;
    } else {
        DBG(BLUE"Get env : ${SERVER_PORT} = {%s}\n"NONE, S_PORT);
    }

    if ((S_NAME = get_config_value("../config/configfile", "SERVER_NAME")) == NULL) {
        log_event(LOG_LEVEL_ERROR, "../config/log.txt", LOGT_NEW, "SERVER_NAME lost!\n");
        return -1;
    } else {
        DBG(BLUE"Get env : ${SERVER_NAME} = {%s}\n"NONE, S_NAME);
        strcpy(LogMessage->name, S_NAME);
    }

    if ((S_PASSWD = get_config_value("../config/configfile", "SERVER_PASSWD")) == NULL) {
        log_event(LOG_LEVEL_ERROR, "../config/log.txt", LOGT_NEW, "SERVER_PASSWD lost!\n");
        return -1;
    } else {
        DBG(BLUE"Get env : ${SERVER_PASSWD} = {%s}\n"NONE, S_PASSWD);
        strcpy(LogMessage->passwd, S_PASSWD);
    }
    
    // 表示成功
    return 1;
}
