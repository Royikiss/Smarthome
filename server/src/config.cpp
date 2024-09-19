/*************************************************************************
	> File Name: config.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun 15 Sep 2024 11:50:39 PM CST
 ************************************************************************/


#include "../include/config.h"

std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    size_t last = str.find_last_not_of(" \t\n\r");
    return (first == std::string::npos || last == std::string::npos) ? "" : str.substr(first, last - first + 1);
}


std::string getConfig(const std::string configFile, const std::string keyWord) {
    std::ifstream file(configFile);  // 打开文件
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file " << configFile << std::endl;
        return "";
    }

    std::string line;
    while (std::getline(file, line)) {  // 逐行读取
        // 去掉一行中的首尾空格
        line = trim(line);

        // 找到等号的位置
        size_t equalPos = line.find('=');
        if (equalPos != std::string::npos) {
            // 提取 key 和 value
            std::string key = trim(line.substr(0, equalPos));
            std::string value = trim(line.substr(equalPos + 1));

            // 如果 key 匹配，就返回对应的 value
            if (key == keyWord) {
                return value;
            }
        }
    }

    // 如果没有找到对应的关键词，返回空字符串
    return "";
}
