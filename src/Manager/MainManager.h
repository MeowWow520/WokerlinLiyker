#pragma once 

#ifndef MAINMANAGER_H
#define MAINMANAGER_H
#include <iostream>
#include "SITemplate.h"
#include "spdlog/spdlog.h"


class MainManager : public SITemplate<MainManager> {
    friend class SITemplate<MainManager>;

public:
    MainManager();
    ~MainManager();
    // 主应用程序运行函数
    int RunApplication(int argc, char** argv);


protected:
    // 关闭应用程序
    void Shutdown();
    // 设置日志记录级别
    bool SetLoggerLevel(spdlog::level::level_enum level);
private:
    bool IsRunning = true;
};

#endif // !MAINMANAGER_H