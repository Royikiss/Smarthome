/*************************************************************************
	> File Name: color.h
	> Author:Royi 
	> Mail:royi990001@gmail.com 
	> Created Time: Tue 07 May 2024 12:10:46 PM CST
	> Describe: 
 ************************************************************************/
#ifndef _COLOR_H__
#define _COLOR_H__

namespace SH {

// 定义颜色和样式宏，使用格式化的方式
#define COLOR(a, b) "\e[0;" #b "m" a "\e[0m"   // 普通颜色
#define L_COLOR(a, b) "\e[1;" #b "m" a "\e[0m" // 亮色

// 常用颜色宏定义
#define BLACK(a) COLOR(a, 30)    // 黑色
#define L_BLACK(a) L_COLOR(a, 30) // 亮黑色，偏灰
#define RED(a) COLOR(a, 31)      // 红色
#define L_RED(a) L_COLOR(a, 31)  // 亮红色
#define GREEN(a) COLOR(a, 32)    // 绿色
#define L_GREEN(a) L_COLOR(a, 32) // 亮绿色

// 其他颜色宏定义
#define BROWN(a) COLOR(a, 33)    // 棕色
#define L_BROWN(a) L_COLOR(a, 33) // 亮棕色
#define YELLOW(a) COLOR(a, 33)   // 黄色
#define L_YELLOW(a) L_COLOR(a, 33) // 亮黄色
#define BLUE(a) COLOR(a, 34)     // 蓝色
#define L_BLUE(a) L_COLOR(a, 34) // 亮蓝色
#define PINK(a) COLOR(a, 35)     // 粉色
#define L_PINK(a) L_COLOR(a, 35) // 亮粉色
#define CYAN(a) COLOR(a, 36)     // 青色
#define L_CYAN(a) L_COLOR(a, 36) // 亮青色
#define GRAY(a) COLOR(a, 37)     // 灰色
#define L_GRAY(a) L_COLOR(a, 37) // 亮灰色
#define WHITE(a) L_COLOR(a, 37)  // 白色

// 样式宏定义
#define BOLD(a) "\e[1m" a "\e[0m"        // 粗体
#define UNDERLINE(a) "\e[4m" a "\e[0m"   // 下划线
#define BLINK(a) "\e[5m" a "\e[0m"       // 闪烁
#define REVERSE(a) "\e[7m" a "\e[0m"     // 反转颜色
#define HIDE(a) "\e[8m" a "\e[0m"        // 隐藏
#define CLEAR "\e[2J"                    // 清除屏幕
#define CLRLINE "\r\e[K"                 // 清除行
 
}
#endif

