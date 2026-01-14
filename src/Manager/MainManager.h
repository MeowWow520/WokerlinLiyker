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



class SceneBaseClass;

class MainManager : public SITemplate<MainManager> {
    friend class SITemplate<MainManager>;

public:
    // 构造函数与析构函数
    MainManager();
    ~MainManager();
    // 主应用程序运行函数
    int RunApplication(int argc, char** argv);
    void HandEvent(SDL_Event *Event);
    void Update();
    void Rander();


    /** 断言失败处理函数
     *  @param Condition 断言条件，若为true则触发断言失败
     *  @param Message 断言失败时的提示信息
     */
    void AssertionFailure(bool Condition, const char* Message);
    /** 切换场景
     *  @param NewScene 新场景指针
     */
    void ChangeScene(SceneBaseClass* NewScene) {
        if (CurrentScene != nullptr) {
            CurrentScene->Clean();
            delete CurrentScene;
        }
        CurrentScene = NewScene;
        CurrentScene->Init();
    }
    SDL_Event* GetSDLEvent() { return &SDLEvent; }
    SDL_Window* GetSDLWindow() { return SDLWindow; }
    SDL_Renderer* GetSDLRenderer() { return SDLRenderer; }
    SDL_Point GetPosCursor() { return PosCursor; }
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
    SceneBaseClass* CurrentScene = nullptr;

};

#endif // !MAINMANAGER_H