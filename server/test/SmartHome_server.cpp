/*************************************************************************
	> File Name: SmartHome_server.cpp
	> Author:Royi 
	> Mail:royi990001@gmail.com 
	> Created Time: Mon 29 Jul 2024 08:15:49 PM CST
	> Describe: 
 ************************************************************************/

#include "../include/head.h"

#define BACKLOG 5
#define MAX_EVENTS 10

pid_t slave_reactor_pid;
int bridge[2]; // 父子进程套接字通讯域套接字

int main() {
    // 规范服务器退出信号
    signal(SIGINT, signalHandler);
    if ((socketpair(AF_UNIX, SOCK_STREAM, 0, bridge)) < 0) {
        perror("socketpair");
        exit(EXIT_FAILURE);
    }

    if ((slave_reactor_pid = fork()) < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (slave_reactor_pid == 0) {
        DBG("从反应堆: 从反应堆正常启动\n");
        // 从反应堆
        close(bridge[1]);
        int clients[MAX_EVENTS];                    // 哈希,记录当前打开的文件描述符,0号位置记录最大值
        Cgo::thread_pool pool(6);                   // 线程池
        epoll_event ev, events[MAX_EVENTS];         // 事件
        UsrMsg tusg;                                // 从主反应堆发来的数据
        std::map<std::string, int> u2f;             // 用户名与文件描述符的对应关系
        std::map<int, std::string> f2u;             // 文件描述符与用户名的对应关系
        int epoll_fd = epoll_create1(0);            // 事件监控
        int client_fd;

        if (epoll_fd == -1) {
            perror("epoll_create1 failed");
            exit(EXIT_FAILURE);
        }

        make_nonblock(bridge[0]);

        // 监听 bridge[0]，用于接收主反应堆发来的文件描述符
        ev.events = EPOLLIN;
        ev.data.fd = bridge[0];
        if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, bridge[0], &ev) == -1) {
            perror("epoll_ctl failed for bridge[0]");
            exit(EXIT_FAILURE);
        }

        while(true) {
            int nfds = epoll_wait(epoll_fd, events, 10, -1);
            if (nfds == -1) {
                perror("epoll_wait failed");
                continue;
            }
            for (int i = 0; i < nfds; ++i) {
                int event_fd = events[i].data.fd;

                if (event_fd == bridge[0] && (events[i].events & EPOLLIN)) {
                    // 从 bridge[0] 接收文件描述符
                    client_fd = recv_UsrMsg(bridge[0], tusg);
                    if (client_fd < 0) {
                        std::cout << "文件描述符获取失败" << std::endl;
                    } else {
                        std::cout << "收到文件描述符成功: [" << client_fd << "]" << std::endl; 

                        clients[client_fd] = true;           // 添加到监控列表中
                        u2f[tusg.username] = client_fd;      // 建立文件描述符和用户名的对应关系
                        f2u[client_fd] = tusg.username;

                        if ((make_nonblock(client_fd)) < 0) {
                            perror("make_nonblock");
                            exit(EXIT_FAILURE);
                        }

                        // 添加客户端 socket 到 epoll 监控
                        ev.events = EPOLLIN | EPOLLET;
                        ev.data.fd = client_fd;
                        if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &ev) == -1) {
                            perror("epoll_ctl failed");
                            continue;
                        }
                    }
                } 

                else if (events[i].events & EPOLLIN) {
                    // 处理客户端请求
                    DBG("从反应堆: 会话 [%d] 出现请求, 添加到任务队列\n", event_fd);
                    pool.add_task(events_handle, event_fd, u2f, f2u);
                }
            }
        }
    } else {
        // 主反应堆
        DBG("主反应堆启动中...\n");
        close(bridge[0]);
        Cgo::thread_pool login_pool(3);
        int server, client;
        if ((server = socket_create(8081)) < 0) {
            perror("create_socket");
            exit(EXIT_FAILURE);
        }
        
        DBG("主反应堆:  正常接收登陆请求...\n");
        while (true) {
            sockaddr_in client_addr;
            memset(&client_addr, 0, sizeof(client_addr));
            socklen_t client_addr_len = sizeof(client_addr);
            if ((client = accept(server, (struct sockaddr *)&client_addr, &client_addr_len)) < 0) {
                perror("accept");
                exit(EXIT_FAILURE);
            }
            login_pool.add_task(loginFunction, bridge[1], client);
        }
    }
    return 0;
}
