#pragma once

#ifndef CONSOLEOUTPUT_H
#define CONSOLEOUTPUT_H
#include <iostream>
#include <iomanip>
#include <ctime>
#include "DefineClass/MessageType.h"


/** ConsoleOutput.h 提供控制台输出的函数
 * 
 *  包含输出当前时间等功能
 */
class ConsoleOutput {

public:
    /** 打印当前时间的静态函数 
     *  -->
     *  趣事: 一开始我用的是 std::localtime 函数，但它在多线程环境下是不安全的
     *  后来改用 localtime_s 函数，但 Github Copilot 自动补全给我补的是 std::localtime_s
     *  这个函数实际上并不存在，导致编译错误。所以我不得以换回了 std::localtime
     *  但这时又出现了线程安全问题。MSVC 报警告 C4996
     *  ```
     *  'localtime': This function or variable may be unsafe. Consider using localtime_s instead. 
     *  To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.MSVC(C4996)
     *  ```
     *  但我并不知道如何使用#define _CRT_SECURE_NO_WARNINGS 来禁用这个警告
     *  我尝试了在本头文件开头添加 #define _CRT_SECURE_NO_WARNINGS，没有效果
     *  在 #pragma once 之后添加也没有效果
     *  在 #include 之前之后添加也没有效果
     *  直到最后才注意到你得在 main.cpp 文件的最开头添加这个宏定义，才成功禁用了这个警告
     *  <--
     */
    static void PrintCurrentTime() {
        std::time_t now = std::time(nullptr);
        std::tm localTime;
        localtime_s(&localTime, &now);
        std::cout << "[" << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S") << "] ";
    }
    // 根据消息类型打印消息的静态函数
    static void PrintMessage(MessageType type, const std::string& message) {
        PrintCurrentTime();
        switch (type) {
        case MessageType::SYSTEM:
            std::cout << "[SYSTEM] " << message << std::endl;
            break;
        case MessageType::WARNING:
            std::cout << "[WARNING] " << message << std::endl;
            break;
        case MessageType::ERROR:
            std::cerr << "[ERROR] " << message << std::endl;
            break;
        case MessageType::DEBUG:
            std::cout << "[DEBUG] " << message << std::endl;
            break;
        default:
            std::cout << "[UNKNOWN] " << message << std::endl;
            break;
        }
    }
private:
    ConsoleOutput() = default;
    ~ConsoleOutput() = default;

protected:

};

#endif // !CONSOLEOUTPUT_H