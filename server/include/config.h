/*************************************************************************
	> File Name: config.h
	> Author: 
	> Mail: 
	> Created Time: Sun 15 Sep 2024 11:48:03 PM CST
 ************************************************************************/

#ifndef _CONFIG_H
#define _CONFIG_H

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>  // 用于去除空格

// 去除字符串两边的空格
std::string trim(const std::string& str);

std::string getConfig(const std::string configFile, const std::string keyWord);

#endif
