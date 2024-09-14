/*************************************************************************
	> File Name: send_chat.c
	> Author:Royi 
	> Mail:royi990001@gmail.com 
	> Created Time: Fri 10 May 2024 02:04:51 PM CST
	> Describe: 
 ************************************************************************/

#include "../include/head.h"
#include "../include/send_chat.h"

extern int sockfd;
extern WINDOW *input_sub, *input_win;
extern struct SmhMsg chat_msg;
extern char *S_IP;                         // 服务器端IP地址
extern char *S_PORT;                       // 服务器端端口地址
extern char *S_NAME;                       // 用户名
extern char *S_PASSWD;                     // 密码

void send_chat() {
    echo();
    nocbreak();
    bzero(chat_msg.msg, sizeof(chat_msg.msg));
    chat_msg.type = SMH_WALL;
    curs_set(1);
    w_gotoxy_puts(input_win, 1, 1, "Input Message : ");
    mvwscanw(input_win, 2, 10, "%[^\\n]s", chat_msg.msg);
    //判断如果读入的信息非空，则发送到服务端
    if (strlen(chat_msg.msg)) {
	    struct SmhMsg tmpmsg;
	    tmpmsg = chat_msg;
		// 分析指令，发送相应的包
        // 如果是私聊
        if (tmpmsg.msg[0] == '@') {
            strcpy(tmpmsg.name, strtok(tmpmsg.msg + 1, " "));
            tmpmsg.type = SMH_MSG;
            send(sockfd, (void *)&tmpmsg, sizeof(tmpmsg), 0);
        } else {
            // 不是私聊，是控制信息
		    tmpmsg.ctl = parse_ctl(tmpmsg.msg);
            if (tmpmsg.ctl.action == -1) {
                // 群聊信息
                strcpy(tmpmsg.name, S_NAME);
                tmpmsg.type = SMH_WALL;
                send(sockfd, (void *)&tmpmsg, sizeof(tmpmsg), 0);
            } else {
                // 设备控制信息
                strcpy(tmpmsg.name, S_NAME);
                tmpmsg.type = SMH_CTL;
                send(sockfd, (void *)&tmpmsg, sizeof(tmpmsg), 0);
            }
        }
		
    }
    wclear(input_win);
    curs_set(0);
    box(input_win, 0, 0);
    wrefresh(input_win);
    noecho();
    cbreak();
}


// 定义一个解析控制字符串的函数
struct Ctl parse_ctl(char *ctl_str) {
    // 初始化一个Ctl结构体
    struct Ctl ctl = {0};

    // 使用strtok函数分割字符串，以空格为分隔符
    char *instruction = strtok(ctl_str, " ");

    // 如果字符串为空，则将action设为-1并返回ctl
    if (instruction == NULL) {
        ctl.action = -1;
        return ctl;
    }

    // 根据不同的指令设置不同的action和设备状态
    if (strcmp(instruction, "#1") == 0) {
        ctl.action = ACTION_GET_DEVICES;
    } else if (strcmp(instruction, "#21") == 0) {
        // 修改设备状态为开
        ctl.action = ACTION_UPDATE_DEVICE;
        char *dev_id_str = strtok(NULL, " ");
        if (dev_id_str == NULL) {
            ctl.action = -1;
            return ctl;
        }
        ctl.dev.device_id = atoi(dev_id_str);
        ctl.dev.state = DEVICE_STATE_ON;
    } else if (strcmp(instruction, "#22") == 0) {
        ctl.action = ACTION_UPDATE_DEVICE;
        char *dev_id_str = strtok(NULL, " ");
        if (dev_id_str == NULL) {
            ctl.action = -1;
            return ctl;
        }
        ctl.dev.device_id = atoi(dev_id_str);
        ctl.dev.state = DEVICE_STATE_OFF;
    } else if (strcmp(instruction, "#23") == 0) {
        // 更改设备状态为待机
        ctl.action = ACTION_UPDATE_DEVICE;
        char *dev_id_str = strtok(NULL, " ");
        if (dev_id_str == NULL) {
            ctl.action = -1;
            return ctl;
        }
        ctl.dev.device_id = atoi(dev_id_str);
        ctl.dev.state = DEVICE_STATE_STANDBY;
    } else if (strcmp(instruction, "#31") == 0) {
        // 添加设备灯
        ctl.action = ACTION_ADD_DEVICE;
        ctl.dev.type = DEVICE_LIGHT;
        char *dev_name = strtok(NULL, " ");
        if (dev_name == NULL) {
            ctl.action = -1;
            return ctl;
        }
        strncpy(ctl.dev.device_name, dev_name, sizeof(ctl.dev.device_name) - 1);
    } else if (strcmp(instruction, "#32") == 0) {
        // 添加设备开关
        ctl.action = ACTION_ADD_DEVICE;
        ctl.dev.type = DEVICE_SWITCH;
        char *dev_name = strtok(NULL, " ");
        if (dev_name == NULL) {
            ctl.action = -1;
            return ctl;
        }
        strncpy(ctl.dev.device_name, dev_name, sizeof(ctl.dev.device_name) - 1);
    } else if (strcmp(instruction, "#33") == 0) {
        // 添加设备恒温设备
        ctl.action = ACTION_ADD_DEVICE;
        ctl.dev.type = DEVICE_THERMOSTAT;
        char *dev_name = strtok(NULL, " ");
        if (dev_name == NULL) {
            ctl.action = -1;
            return ctl;
        }
        strncpy(ctl.dev.device_name, dev_name, sizeof(ctl.dev.device_name) - 1);
    } else if (strcmp(instruction, "#4") == 0) {
        // 删除设备
        ctl.action = ACTION_DEL_DEVICE;
        char *dev_id_str = strtok(NULL, " ");
        if (dev_id_str == NULL) {
            ctl.action = -1;
            return ctl;
        }
        ctl.dev.device_id = atoi(dev_id_str);
    } else {
        ctl.action = -1;
    }

    // 返回解析后的Ctl结构体
    return ctl;
}

