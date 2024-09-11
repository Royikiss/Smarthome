/*************************************************************************
	> File Name: common.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 11 Sep 2024 07:53:22 PM CST
 ************************************************************************/

#include "../include/head.h"

int _SERVER_VALUE = 0;

char *get_config_value(const char *config_file_path, const char *key) {
        FILE *fp = NULL;
        char *buff = (char *)malloc(sizeof(char) * BUFFSIZE);
        char *pos;  // 用于定位“=”
        memset(_Server_Tmp_, 0, sizeof(_Server_Tmp_));

        size_t len = 0;
        ssize_t read = 0;

        if ((fp = fopen(config_file_path, "r")) == NULL) {
                perror("fopen");
                exit(1);
        }

        while((read = getline(&buff, &len, fp)) != -1) {
                // 寻找key
                pos = strstr(buff, key);
                if (pos == NULL) continue;
                // 定位=
                pos = strchr(buff, '=');

                if (*(pos) == '=') {
                        // 跳过空格
                        while(*(++pos) == ' ');
                        // 拷贝进全局变量
                        int i = 0;
                        while(*(pos) != EOF && *(pos) != '\n' && *(pos) != ' ') {
                                _Server_Tmp_[i++] = *(pos++);
                        }
                        pos = strncpy(_Server_Value_[_SERVER_VALUE], _Server_Tmp_, sizeof(_Server_Tmp_));
                        if (++_SERVER_VALUE >= VARIABLE_NUM) _SERVER_VALUE = 0;
                        break;
                } else {
                        read = -1;
                        break;
                }
        }

        free(buff);
        fclose(fp);
        if (read == -1) {
                return NULL;
        } else {
                return pos;
        }
}
