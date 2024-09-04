/*************************************************************************
	> File Name: log.c
	> Author:Royi 
	> Mail:royi990001@gmail.com 
	> Created Time: Wed 08 May 2024 06:29:27 PM CST
	> Describe: 
 ************************************************************************/

#include "../include/head.h"

void log_event(int level, const char *filename, int log_type, const char *format, ...) {
    time_t now = time(NULL);
    char *level_str;
    FILE *fp;
    va_list args;

    switch(level) {
        case LOG_LEVEL_INFO: {
            level_str = "INFO";
            break;
        }
        case LOG_LEVEL_WARNING: {
            level_str = "WARNING";
            break;
        }
        case LOG_LEVEL_ERROR : {
            level_str = "ERROR";
            break;
        }
        default: {
            level_str = "UNKNOWN";
            break;
        }
    }
    
    fp = fopen(filename, "a");

    if(fp == NULL) {
        perror("[Log]Open file ERROR!");
        return ;
    }

    if(fp != NULL) {
        fprintf(fp, "%s [%s]: ", ctime(&now), level_str);
        va_start(args, format);
        vfprintf(fp, format, args);
        va_end(args);
        fprintf(fp, "\n");
        fclose(fp);
    }
    return ;
}
