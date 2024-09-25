# SmartHome
这个系统最初的设计目的是为了嵌入式智能家居系统而设计的一种对于家庭设备进行操作的后端框架。
其功能包括：
- 添加设备；
- 删除设备；
- 更改设备状态;
- 删除设备；
- 数据库交互。

后来又添加了家庭用户聊天的功能。

具体聊天功能包括：
- 发布公告： 对所有当前在线的用户进行消息发布
- 私聊： 对单独的用户发送消息 

# Quick Starting

client 和 server 对应的分别是客户端和用户端的代码。

在linux系统下，你可以使用已经提供的配置文件信息（路径在 ~/SmartHome/client/config/configfile）来测试客户端的使用（当前功能暂未开放，因为没有添加注册账户的功能）

如果你缺少依赖,也可以使用已经编译好的程序,可以在 `~/SmartHome/build/RoyiSmartHome` 找到

注意,程序不一定能够在所有linux发行版的主机上运行,如果不能运行,请解决依赖问题:

> 依赖项: `ncuress`  `Connector/C++` `thread`

## Make

使用Cmake进行构建：

在
```shell
~/SmartHome/server/build # 服务端程序
~/SmartHome/client/build # 客户端程序
```
中执行:
```shell
cmake ..
make
```

在服务端，你也可以执行：

```bash
cmake -DCMAKE_BUILD_TYPE=Debug ../
make
```

启用Debug模式看到更多信息。

## config

在程序开始工作之前，你可以通过配置:

- 服务端
```bash
/home/royi/SmartHome/server/config/SmartHome.config
```

- 客户端
```bash
/home/royi/SmartHome/client/config/configfile
```

进行程序启动前的一系列准备工作，详细的可配置参数如下：

服务端:
```bash
MYSQLUSR              # 数据库用户名称
MYSQLPASSWORD         # 数据库登陆密码
# 待开发...
```

客户端:
```bash
SERVER_IP             # 服务端的IP地址
SERVER_PORT           # 服务端端口
# 待开发...
```

## running

想要运行客户端程序,在 `~/SmartHome/client/build` 中执行:

    ```bash
    ./RoyiSmartHome -u [username] -p [password] 
    ```

> 注意,再次申明,当前项目并不提供测试用服务器,使用默认配置文件并不能正常登陆(默认配置文件中的IP虽然有效,但对于未知用户,服务器会拒绝服务),请自行编译服务端代码和客户端代码运行测试.
> 测试服务器的注册功能正在开发中...

想要运行服务端程序,在`~/SmartHome/server/build/` 中执行:

    ```bash
    ./RoyiSmartHome
    ```
