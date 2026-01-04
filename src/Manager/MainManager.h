#pragma once

#ifndef MAINMANAGER_H
#define MAINMANAGER_H
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include "SingletonInstanceTemplate.h"
#include "../ConsoleOutput.h"
#include "../DefineClass/MessageType.h"


class MainManager : public SITemplate<MainManager> {
	friend class SITemplate<MainManager>;
public:
	int StartApplication(int argc, char** argv) {
		(void)argc;
		(void)argv;
		ConsoleOutput::PrintMessage(MessageType::SYSTEM, u8"SDL Application is Running...");
		// Main Loop
		while (IsApplicationRunning) {
			while (SDL_PollEvent(&SDLEvent)) 
			{
				InPutMessageProcess();
			}
			// 处理每帧后的操作 - 清屏 && 设置渲染器
			AfterPkMsg();
		}
		return 0;
	}
private:
	MainManager() {
		// SDL 初始化及各个库的断言
		SDLInitializationAssert(!SDL_Init(SDL_INIT_EVERYTHING), u8"SDL");
		SDLInitializationAssert(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG), u8"SDL_image");
		SDLInitializationAssert(Mix_Init(MIX_INIT_MP3), u8"SDL_Mixer");
		SDLInitializationAssert(!TTF_Init(), u8"SDL_TTF");
		// SDL_mixer 音频设置
		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
		// SDL_image 图片设置
		SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
		// 窗口创建及断言
		MainWindow = SDL_CreateWindow(u8"WokerlinLiyker's SDL Application", 
			SDL_WINDOWPOS_CENTERED, 
			SDL_WINDOWPOS_CENTERED, 
			DEFAULTWIDTH, DEFAULTHEIGHT, 
			SDL_WINDOW_SHOWN);
		SDLInitializationAssert(MainWindow, u8"SDL Window");
		// 渲染器创建及断言
		SDLRenderer = SDL_CreateRenderer(MainWindow, -1, 
			SDL_RENDERER_ACCELERATED | 
			SDL_RENDERER_PRESENTVSYNC | 
			SDL_RENDERER_TARGETTEXTURE);
		SDLInitializationAssert(SDLRenderer, u8"SDL Renderer");
	};
	~MainManager() {
		// SDL 资源释放
		SDL_DestroyRenderer(SDLRenderer);
		SDL_DestroyWindow(MainWindow);
		TTF_Quit();
		Mix_Quit();
		IMG_Quit();
		SDL_Quit();
	};

protected:
	const int DEFAULTWIDTH{1980};
	const int DEFAULTHEIGHT{1060};
	bool IsApplicationRunning{true};
	SDL_Event SDLEvent;
	SDL_Point PosCursor = { 0,0 };
	SDL_Window* MainWindow = nullptr;
	SDL_Renderer* SDLRenderer = nullptr;
	bool SDLInitializationAssert(bool condition, const std::string& moduleName) {
		if (condition) {
			ConsoleOutput::PrintMessage(MessageType::SYSTEM, moduleName + " Initialization Succeeded.");
			return true;
		}
		else {
			std::cerr << "[ERROR] " << moduleName << " Initialization Failed: " << SDL_GetError() << std::endl;
			return false; } };
	void InPutMessageProcess() {
		switch (SDLEvent.type) {
		case SDL_QUIT:
			IsApplicationRunning = false;
			break;
		case SDL_MOUSEMOTION:
			PosCursor.x = SDLEvent.motion.x;
			PosCursor.y = SDLEvent.motion.y;
			break;
		default:
			break;
		}
	};
	void AfterPkMsg() {
		// 设置渲染器颜色为白色
		SDL_SetRenderDrawColor(SDLRenderer, 0, 0, 0, 255);
		// 清屏
		SDL_RenderClear(SDLRenderer);
		SDL_RenderPresent(SDLRenderer);
	}
};

#endif //!MAINMANAGER_H