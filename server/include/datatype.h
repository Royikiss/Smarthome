/*************************************************************************
	> File Name: datatype.h
	> Author:Royi 
	> Mail:royi990001@gmail.com 
	> Created Time: Wed 08 May 2024 06:36:04 PM CST
	> Describe: 
 ************************************************************************/
#ifndef _DATATYPE_H__
#define _DATATYPE_H__

enum device_type {
    DEVICE_LIGHT,               // 设备类型：灯
    DEVICE_SWITCH,              // 设备类型：开关
    DEVICE_THERMOSTAT,          // 设备类型：恒温设备
    // 其他设备类型
};

// 设备状态枚举
enum device_state {
    DEVICE_STATE_OFF,           // 设备状态：关闭
    DEVICE_STATE_ON,            // 设备状态：打开
    DEVICE_STATE_STANDBY,       // 设备状态：待机
    // 其他设备状态
};

// 设备结构体
struct device {
    int device_id;              // 设备ID
    char device_name[32];       // 设备名称
    enum device_type type;      // 设备类型
    enum device_state state;    // 设备状态
    // 其他设备属性
};

//登录相关的
struct  LogRequest {
    char name[20];
    char passwd[20];
    char msg[512];
};

struct LogResponse{
    int type; // 0 OK 1 NO
    char msg[512];
};
//登录期间交互
#define MAX_MSG 1024
//日常的消息交互，如聊天信息，统一为512长度

#define ACTION_GET_DEVICES 0x01         // 命令：获取设备
#define ACTION_UPDATE_DEVICE 0x02       // 命令：更新设备
#define ACTION_ADD_DEVICE 0x04          // 命令：添加设备
#define ACTION_DEL_DEVICE 0x08          // 命令：删除设备

//使用CTL报文对设备进行控制
struct Ctl {
    int action;
    //int device_id; 此处更新
    struct device dev;
};

#define SMH_HEART 0x01 //心跳
#define SMH_ACK 0x08 //ack
#define SMH_MSG 0x04 //聊天
#define SMH_WALL 0x02 //公告
#define SMH_CTL 0x10 //控制信息
#define SMH_FIN 0x100 //离场

struct SmhMsg{
    int type;  // type & SMH_HEART 验证是否为SMH_HEART信息
    int size;
    char name[20];
    char msg[MAX_MSG];
    struct Ctl ctl;
};

//新增了User结构体
struct User{
	char name[20];
};
#endif

