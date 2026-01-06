#pragma once 

#ifndef MAINMANAGER_H
#define MAINMANAGER_H
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "SITemplate.h"
#include "spdlog/spdlog.h"


class MainManager : public SITemplate<MainManager> {
    friend class SITemplate<MainManager>;

public:
    // 构造函数与析构函数
    MainManager();
    ~MainManager();
    // 主应用程序运行函数
    int RunApplication(int argc, char** argv);


protected:
    // 关闭应用程序
    void Shutdown();
    // 设置日志输出级别
    bool SetLoggerLevel(spdlog::level::level_enum level);

    void AssertionFailure(bool Condition, const char* Message);
    bool GetIsRunning() const { return IsRunning; }
    void SetIsRunning(bool running) { IsRunning = running; }
    void PrintPrivateVariables() const;
    void SDLPullEvents(SDL_Event& Event);

private:
    // 主循环控制变量
    bool IsRunning{true};
    // 是否打印鼠标移动事件
    bool IsPrintMouseMove{false};
    // 窗口尺寸 - 宽
    int WindowWidth{1280};
    // 窗口尺寸 - 高
    int WindowHeight{720};
    SDL_Event SDLEvent;
	SDL_Point PosCursor = { 0,0 };
    SDL_Window* SDLWindow = nullptr;
    SDL_Renderer* SDLRenderer = nullptr;

};

#endif // !MAINMANAGER_H