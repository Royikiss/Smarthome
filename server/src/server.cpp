/*************************************************************************
	> File Name: ../src/server.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 15 Aug 2024 03:43:12 PM CST
 ************************************************************************/

#include "../include/head.h"
#include "../include/server.h"

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

void events_handle(int sockfd, std::map<std::string, int> &u2f, std::map<int, std::string> &f2u) {
    SmhMsg tmessage;
    ssize_t recv_size = 0;
    if ((recv_size = recv(sockfd, (void *)&tmessage, sizeof(tmessage), 0)) > 0) {
        if (tmessage.type & SMH_MSG) {
            // 聊天信息
            int tf = u2f[tmessage.name];
            if (tf) {
                send(tf, (void *)&tmessage, sizeof(tmessage), 0);
            }
        } else if (tmessage.type & SMH_WALL) {
            // 公告

        } else if (tmessage.type & SMH_CTL) {
            // 控制信息

        } else if (tmessage.type & SMH_FIN) {
            // 退出信息


        }
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
        perror("select error");
        close(client_fd);
        return;
    } else if (ret == 0) {
        // 超时处理
        std::cout << "Login timeout, closing connection" << std::endl;
        close(client_fd);
        return;
    }

    // 接受客户端的登录请求
    if ((size = recv(client_fd, &logReq, sizeof(logReq), 0)) < 0) {
        perror("recv error");
        close(client_fd);
        return;
    }

    // 验证用户名的逻辑
    if (strlen(logReq.name) != 0 && strlen(logReq.passwd) != 0) {
        try {
            sql::mysql::MySQL_Driver *driver;                       // mysql接口
            sql::Connection *con;
            sql::PreparedStatement *pstmt;
            sql::ResultSet *res;

            driver = sql::mysql::get_mysql_driver_instance();
            con = driver->connect("tcp://127.0.0.1:3306", "royi", "xXJiaJiaJia123");
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
    send_UsrMsg(bridge, usr_msg);

    std::cout << "主反应堆认证成功" << std::endl;

    close(client_fd);
    return ;
}

