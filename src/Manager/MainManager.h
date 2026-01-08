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
    /** 设置日志输出级别
     *  @param level 日志级别
     *  @return 设置是否成功
     *  @note 级别包括 trace, debug, info, warn, err, critical, off
     */
    bool SetLoggerLevel(spdlog::level::level_enum level);
    /** 断言失败处理函数
     *  @param Condition 断言条件，若为true则触发断言失败
     *  @param Message 断言失败时的提示信息
     */
    void AssertionFailure(bool Condition, const char* Message);
    /** 获取当前运行状态
     *  @return 当前是否在运行
     */
    bool GetIsRunning() const { return IsRunning; }
    /** 设置当前运行状态
     *  @param running 运行状态
     */
    void SetIsRunning(bool running) { IsRunning = running; }
    /** 打印私有变量状态
     *  @note 仅用于调试
     */
    void PrintPrivateVariables() const;
    /** SDL 事件轮询处理函数
     *  @param Event SDL 事件对象引用
     */
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