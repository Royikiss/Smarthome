/*************************************************************************
	> File Name: chat_ui.h
	> Author:Royi 
	> Mail:royi990001@gmail.com 
	> Created Time: Thu 09 May 2024 07:43:39 PM CST
	> Describe: 
 ************************************************************************/
#ifndef _CHAT_UI_H__
#define _CHAT_UI_H__

#define MSG_WIDTH 100
#define INFO_WIDTH 15
#define MSG_HEIGHT 25
#define INPUT_HEIGHT 5
void destroy_win(WINDOW *win);
void gotoxy(int x, int y);
void gotoxy_putc(int x, int y, int c);
void gotoxy_puts(int x, int y, char* s);
void w_gotoxy_putc(WINDOW *win, int x, int y, int c);
void w_gotoxy_puts(WINDOW *win, int x, int y, char *s);
void init_ui();
void show_info();
void show_message(WINDOW *win, struct User *user, char *msg, int type);

#endif

