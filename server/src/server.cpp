/*************************************************************************
	> File Name: ../src/server.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 15 Aug 2024 03:43:12 PM CST
 ************************************************************************/

#include "../include/head.h"
#include <mysql_driver.h>

extern int slave_reactor_pid;
extern std::map<std::string, int> n2s;

// 服务器终止函数
void signalHandler(int signum) {
    std::cout << "Interrupt signal (" << signum << ") received.\n";
    // 如果子进程存在，首先杀死子进程
    if (slave_reactor_pid != -1) {
        std::cout << "Killing child process with PID: " << slave_reactor_pid << std::endl;
        kill(slave_reactor_pid, SIGKILL);  // 发送 SIGKILL 信号，强制终止子进程
        waitpid(slave_reactor_pid, nullptr, 0);  // 等待子进程终止
    }
    std::cout << "Terminating parent process." << std::endl;
    exit(signum);  // 终止父进程
}

void handle_ctl(int sockfd, SmhMsg &tmessage, std::map<int, std::string> &f2u) {
    try {
        sql::mysql::MySQL_Driver *driver;                       // mysql接口
        sql::Connection *con;
        sql::PreparedStatement *pstmt;
        sql::ResultSet *res;

        driver = sql::mysql::get_mysql_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3306", Envir["MYSQLUSR"].c_str(), Envir["MYSQLPASSWORD"].c_str());
        con->setSchema("SmartHome");
        
        std::string username = tmessage.name;
       
        switch(tmessage.ctl.action) {
            case ACTION_GET_DEVICES : {
                // 得到设备信息
                pstmt = con->prepareStatement("SELECT id, name, state, type FROM devices WHERE `from` = ?");
                pstmt->setString(1, username.c_str());
                res = pstmt->executeQuery();

                std::stringstream device_info;
                device_info << "当前设备有：";
                
                while (res->next()) {
                    int id = res->getInt("id");
                    std::string name = res->getString("name");
                    std::string state = res->getString("state");
                    std::string type = res->getString("type");

                    device_info << "<" << id << ".";
                    if (type == "LIGHT") {
                        device_info << "💡";
                    } else if (type == "SWITCH") {
                        device_info << "🔑";
                    } else if (type == "THERMOSTAT") {
                        device_info << "🌡️";
                    } else {}
                    
                    device_info << "> [" << name << ":";
                    if (state == "ON") {
                        device_info << "开 → ✅";
                    } else if (state == "OFF") {
                        device_info << "关 → ❌";
                    } else if (state == "STANDBY") {
                        device_info << "待机 → ⏸";
                    } else {
                        device_info << "未知状态 → ❓";
                    } 
                    device_info << "] ";
                }
                strncpy(tmessage.msg, device_info.str().c_str(), MAX_MSG - 1);
                tmessage.msg[MAX_MSG - 1] = '\0';  // 确保消息以 '\0' 结尾
                send(sockfd, (void *)&tmessage, sizeof(tmessage), 0);
                delete res;
                delete pstmt;
                break;
            }
            case ACTION_UPDATE_DEVICE: {
                // 更新设备状态
                int device_id = tmessage.ctl.dev.device_id;
                enum device_state new_state = tmessage.ctl.dev.state;
                std::stringstream device_info;
                
                pstmt = con->prepareStatement("UPDATE devices SET state = ? WHERE id = ? AND `from` = ?");

                // 根据设备状态设置数据库中的 state 字段
                if (new_state == DEVICE_STATE_ON) {
                    pstmt->setString(1, "ON");
                } else if (new_state == DEVICE_STATE_OFF) {
                    pstmt->setString(1, "OFF");
                } else if (new_state == DEVICE_STATE_STANDBY) {
                    pstmt->setString(1, "STANDBY");
                }

                device_info << "更新设备状态成功";

                pstmt->setInt(2, device_id);
                pstmt->setString(3, username.c_str());
                pstmt->executeUpdate();

                strncpy(tmessage.msg, device_info.str().c_str(), MAX_MSG - 1);
                tmessage.msg[MAX_MSG - 1] = '\0';  // 确保消息以 '\0' 结尾
                send(sockfd, (void *)&tmessage, sizeof(tmessage), 0);

                delete pstmt;
                break;
            }
            case ACTION_ADD_DEVICE: {
                // 添加新设备
                struct device new_device = tmessage.ctl.dev;
                std::stringstream device_info;
                pstmt = con->prepareStatement("INSERT INTO devices (name, `from`, state, type) VALUES (?, ?, ?, ?)");

                pstmt->setString(1, new_device.device_name);
                pstmt->setString(2, username.c_str());

                // 根据设备状态设置数据库中的 state 字段
                if (new_device.state == DEVICE_STATE_ON) {
                    pstmt->setString(3, "ON");
                } else if (new_device.state == DEVICE_STATE_OFF) {
                    pstmt->setString(3, "OFF");
                } else if (new_device.state == DEVICE_STATE_STANDBY) {
                    pstmt->setString(3, "STANDBY");
                }

                // 设置设备类型
                pstmt->setString(4, (new_device.type == DEVICE_LIGHT) ? "LIGHT" : 
                                       (new_device.type == DEVICE_SWITCH) ? "SWITCH" : "THERMOSTAT");

                pstmt->executeUpdate();

                DBG("检测到用户" L_YELLOW("%s") "添加了一个" L_BLUE("%s") "\n", username.c_str(), new_device.device_name);

                device_info << "成功添加了一个" << new_device.device_name;

                strncpy(tmessage.msg, device_info.str().c_str(), MAX_MSG - 1);
                tmessage.msg[MAX_MSG - 1] = '\0';  // 确保消息以 '\0' 结尾
                send(sockfd, (void *)&tmessage, sizeof(tmessage), 0);
                
                delete pstmt;
                break;
            }
            case ACTION_DEL_DEVICE: {
                // 删除设备
                int device_id = tmessage.ctl.dev.device_id;
                std::stringstream device_info;

                pstmt = con->prepareStatement("DELETE FROM devices WHERE id = ? AND `from` = ?");
                pstmt->setInt(1, device_id);
                pstmt->setString(2, username.c_str());
                pstmt->executeUpdate();

                device_info << "成功删除";

                strncpy(tmessage.msg, device_info.str().c_str(), MAX_MSG - 1);
                tmessage.msg[MAX_MSG - 1] = '\0';  // 确保消息以 '\0' 结尾
                send(sockfd, (void *)&tmessage, sizeof(tmessage), 0);

                delete pstmt;
                break;
            }
            default: {
                std::cerr << "Unknown action type" << std::endl;
                break;
            }
        }
        delete con;
    }  catch (sql::SQLException &e) {
        std::cerr << "MySQL error: " << e.what() << std::endl;
    }
    return ;
}

void loginFunction(int bridge, int client_fd) {
    // 设置套接字为非阻塞模式
    make_nonblock(client_fd);

    fd_set readfds;
    timeval timeout;
    ssize_t size;
    // 登陆相关信息的初始化
    LogRequest logReq;
    LogResponse logResp;
    memset(&logReq, 0, sizeof(logReq));
    memset(&logResp, 0, sizeof(logResp));

    // 设置1秒超时
    FD_ZERO(&readfds);
    FD_SET(client_fd, &readfds);
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;
    
    // 开始监听
    int ret = select(client_fd + 1, &readfds, NULL, NULL, &timeout);

    if (ret == -1) {
        // 错误连接处理
        DBG("主反应堆: 套接字监听错误,线程退出\n");
        perror("select error");
        close(client_fd);
        return;
    } else if (ret == 0) {
        // 超时处理
        DBG("主反应堆: 登陆超时,断开连接\n");
        close(client_fd);
        return;
    }

    // 接受客户端的登录请求
    if ((size = recv(client_fd, &logReq, sizeof(logReq), 0)) < 0) {
        DBG("主反应堆: 接收登陆信息错误,断开连接\n");
        perror("recv error");
        close(client_fd);
        return;
    }

    DBG("主反应堆: 检测到用户名为 [%s] 的登陆请求,开始验证...\n", logReq.name);

    // 验证用户名的逻辑
    if (strlen(logReq.name) != 0 && strlen(logReq.passwd) != 0) {
        try {
            sql::mysql::MySQL_Driver *driver;                       // mysql接口
            sql::Connection *con;
            sql::PreparedStatement *pstmt;
            sql::ResultSet *res;

            driver = sql::mysql::get_mysql_driver_instance();
            con = driver->connect("tcp://127.0.0.1:3306", Envir["MYSQLUSR"].c_str(), Envir["MYSQLPASSWORD"].c_str());
            con->setSchema("SmartHome");

            // 查找用户名并验证密码
            pstmt = con->prepareStatement("SELECT passwd FROM user WHERE name = ?");
            pstmt->setString(1, logReq.name);
            res = pstmt->executeQuery();

            if (res->next()) {
                std::string stored_passwd = res->getString("passwd");

                // 验证密码是否正确
                if (stored_passwd == logReq.passwd) {
                    // 登录成功，更新状态
                    logResp.type = 0;  // 登录成功
                    strcpy(logResp.msg, "Login successful");

                    delete pstmt;
                    pstmt = con->prepareStatement("UPDATE user SET state = ? WHERE name = ?");
                    pstmt->setInt(1, 1);  // 设置状态为已登录
                    pstmt->setString(2, logReq.name);
                    pstmt->executeUpdate();
                } else {
                    logResp.type = 1;  // 登录失败
                    strcpy(logResp.msg, "Invalid credentials");
                }
            } else {
                logResp.type = 1;  // 登录失败
                strcpy(logResp.msg, "Invalid credentials");
            }

            // 清理资源
            delete res;
            delete pstmt;
            delete con;
        } catch (sql::SQLException &e) {
            std::cerr << "MySQL error: " << e.what() << std::endl;
            logResp.type = 1;  // 登录失败
            strcpy(logResp.msg, "Login failed");
        }
    } else {
        logResp.type = 1;  // 登录失败
        strcpy(logResp.msg, "Invalid credentials");
        send(client_fd, &logResp, sizeof(logResp), 0);
        close(client_fd);
        return ;
    }

    // 发送登录响应
    if ((size = send(client_fd, &logResp, sizeof(logResp), 0)) < 0) {
        perror("send error");
    }

    UsrMsg usr_msg;
    usr_msg.fd = client_fd;
    strcpy(usr_msg.username, logReq.name);
    DBG("主反应堆: 用户名为 [%s] 的登陆验证通过, 发送至子反应堆\n", logReq.name);
    send_UsrMsg(bridge, usr_msg);

    std::cout << "usr ["<< logReq.name << "] " << "登陆成功" << std::endl;

    close(client_fd);
    DBG("主反应堆: 线程正常退出\n");
    return ;
}

// 对于每一个连接的事务处理
void events_handle(int sockfd, std::map<std::string, int> &u2f, std::map<int, std::string> &f2u, bool *heart_ctl) {
    SmhMsg msg_tmp, msg_pre, msg;
    size_t msg_size = sizeof(msg);
    ssize_t offset = 0, recv_size = 0, send_size;

    bzero(&msg_pre, sizeof(msg_pre));
    bzero(&msg_tmp, sizeof(msg_tmp));
    bzero(&msg, sizeof(msg));

    while (1) {
        bzero(&msg_tmp, sizeof(msg_tmp));
        if (offset) {
            memcpy(&msg, &msg_pre, offset);
        }
        while((recv_size = recv(sockfd, (void *)&msg_tmp, msg_size, 0)) > 0) {
            if (offset + recv_size == msg_size) {
                memcpy((char *)&msg + offset, (char *)&msg_tmp, recv_size);
                offset = 0;
                break;
            } else if (offset + recv_size < msg_size) {
                memcpy((char *)&msg + offset, (char *)&msg_tmp, recv_size);
                offset += recv_size;
            } else if (offset + recv_size > msg_size) {
                int wait = recv_size - offset;
                memcpy((char *)&msg + offset, (char *)&msg_tmp, wait);
                offset = recv_size - wait;
                memcpy((char *)&msg_pre, (char *)&msg_tmp + wait, offset);
                break;
            }
        }

        if (msg.type & SMH_ACK) {
            // 心跳信息
            DBG("子反应堆[事务处理]: 接受到来自用户 [%s] 的心跳回复\n", f2u[sockfd].c_str());
            heart_ctl[sockfd] = false;
        } else if (msg.type & SMH_MSG) {
            // 聊天信息
            int tf = u2f[msg.name];
            if (tf) {
                DBG("子反应堆[事务处理]: [%s] 向 [%s] 说: \"s\"\n", f2u[sockfd].c_str(), msg.name, msg.msg);
                send(tf, (void *)&msg, sizeof(msg), 0);
            }
        } else if (msg.type & SMH_WALL) {
            // 公告
            for (std::map<std::string, int>::iterator it = u2f.begin(); it != u2f.end(); ++it) {
                send(it->second, (void *)&msg, sizeof(msg), 0);
            }
            DBG("子反应堆[事务处理]: [%s] 向 所有人[All] 说: \"%s\" \n", f2u[sockfd].c_str(), msg.msg);
        } else if (msg.type & SMH_CTL) {
            // 控制信息
            DBG("子反应堆[事务处理]: 触发设备控制操作,转向设备中心处理...\n");
            handle_ctl(sockfd, msg, f2u);
        } else if (msg.type & SMH_FIN) {
            DBG("子反应堆[事务处理]: 用户 [%s] 申请退出,执行数据同步操作...\n", f2u[sockfd].c_str());
            // 退出信息
            std::string sender_name = f2u[sockfd];
            // 在 MySQL 中修改该用户的状态为未登录
            try {
                sql::mysql::MySQL_Driver *driver;
                sql::Connection *con;
                sql::PreparedStatement *pstmt;

                driver = sql::mysql::get_mysql_driver_instance();
                con = driver->connect("tcp://127.0.0.1:3306", Envir["MYSQLUSR"].c_str(), Envir["MYSQLPASSWORD"].c_str());
                con->setSchema("SmartHome");

                // 更新登录状态，设置 state 为 0 表示用户下线
                pstmt = con->prepareStatement("UPDATE user SET state = ? WHERE name = ?");
                pstmt->setInt(1, 0);  // 设置状态为未登录
                pstmt->setString(2, sender_name.c_str());
                pstmt->executeUpdate();

                delete pstmt;
                delete con;
            } catch (sql::SQLException &e) {
                std::cerr << "MySQL error: " << e.what() << std::endl;
            }
            // 关闭连接并退出
            u2f.erase(sender_name);
            f2u.erase(sockfd);
            close(sockfd);
        }
        DBG("子反应堆[事务处理]: 线程正常退出\n");
        return ;
    }
    return ;
}

void HeartSending(std::map<std::string, int> &u2f, std::map<int, std::string> &f2u, bool *heart_ctl) {
    int max_socket = 0;
    SmhMsg smsg;
    smsg.type = SMH_HEART;
    std::queue<int> checking_socket;
    try {
        sql::mysql::MySQL_Driver *driver;
        sql::Connection *con;
        sql::PreparedStatement *pstmt;

        driver = sql::mysql::get_mysql_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3306", Envir["MYSQLUSR"].c_str(), Envir["MYSQLPASSWORD"].c_str());
        con->setSchema("SmartHome");

        while (true) {
            sleep(10);
            while (!checking_socket.empty()) {
                if (heart_ctl[checking_socket.front()] == true) {
                    // 心跳未回应强制退出
                    DBG(L_RED("[心跳监测]: 用户[%s]未回应心跳, 强制退出\n") , f2u[checking_socket.front()].c_str());
                    pstmt = con->prepareStatement("UPDATE user SET state = ? WHERE name = ?");
                    pstmt->setInt(1, 0); 
                    pstmt->setString(2, f2u[checking_socket.front()].c_str());
                    pstmt->executeUpdate();

                    u2f.erase(f2u[checking_socket.front()]);
                    f2u.erase(checking_socket.front());
                    close(checking_socket.front()); // 关闭连接
                        
                    delete pstmt;
                    delete con;
                }
                checking_socket.pop();
            }
            DBG(L_RED("[心跳监测]: 新一轮的心跳监测开始了...\n"));
            for (std::map<std::string, int>::iterator it = u2f.begin(); it != u2f.end(); ++it) {
                DBG(L_RED("[♥️]: Send ♥️ to [%s]\n") , it->first.c_str());
                checking_socket.push(it->second);
                heart_ctl[it->second] = true;
                send(it->second, (void *)&smsg, sizeof(smsg), 0);
            }
        }
    } catch (sql::SQLException &e) {
        std::cerr << "MySQL error: " << e.what() << std::endl;
    }
    return ;
}
