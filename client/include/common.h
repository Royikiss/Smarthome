/*************************************************************************
	> File Name: common.h
	> Author:Royi 
	> Mail:royi990001@gmail.com 
	> Created Time: Sat 04 May 2024 05:09:31 PM CST
	> Describe: 
 ************************************************************************/
#ifndef _COMMON_H__
#define _COMMON_H__

#define BUFFSIZE 1024 
#define VARIABLE_NUM 16 
#define VALUE_SIZE 64 

#define DEFARG(name, default_value) ((#name[0]) ? (name + 0) : default_value)
extern WINDOW *message_sub;
#define Show_Message(arg0, arg1, arg2, arg3) show_message(DEFARG(arg0, message_sub), DEFARG(arg1, NULL), arg2, DEFARG(arg3, 0))

extern char *S_IP;
extern char *S_PORT;
extern char *S_NAME;
extern char *S_PASSWD;

/*   value in config   */
extern int _SERVER_VALUE;
extern char _Server_Tmp_[VALUE_SIZE];
extern char _Server_Value_[VARIABLE_NUM][VALUE_SIZE];

/*      function       */
char *get_config_value(const char *config_file_path, const char *key);

#endif
