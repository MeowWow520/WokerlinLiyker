#include "MainManager.h"
#include "../Scene/SceneMainTitle.h"


MainManager::MainManager() {
    /** 设置日志输出级别
     *  @note 级别包括 trace, debug, info, warn, err, critical, off
     */
    spdlog::set_level(spdlog::level::info);
    spdlog::info("MainManager initialized.");

    MainManager::AssertionFailure(!SDL_Init(SDL_INIT_EVERYTHING), u8"SDL");
    MainManager::AssertionFailure(!TTF_Init(), u8"SDL_ttf");
    MainManager::AssertionFailure(Mix_Init(MIX_INIT_MP3), u8"SDL_mixer");
    MainManager::AssertionFailure(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG), u8"SDL_image");
    // 打开音频，设置音频格式
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
	SDLWindow = SDL_CreateWindow(u8"WokerlinLiyker's Application", 
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
			WindowWidth, WindowHeight, SDL_WINDOW_SHOWN);
    
	MainManager::AssertionFailure(SDLWindow, u8"SDL Window");
	SDLRenderer = SDL_CreateRenderer(SDLWindow, -1, 
		SDL_RENDERER_ACCELERATED | 
        SDL_RENDERER_PRESENTVSYNC | 
        SDL_RENDERER_TARGETTEXTURE);
	MainManager::AssertionFailure(SDLRenderer, u8"SDL Renderer");

}

MainManager::~MainManager() {
    SDL_DestroyRenderer(SDLRenderer);
	SDL_DestroyWindow(SDLWindow);
	TTF_Quit();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
    spdlog::info("MainManager destroyed.");

}

int MainManager::RunApplication(int argc, char** argv) {
    (void)argc; (void)argv;
    // Main application loop
    spdlog::info("Application Started.");
    while (GetIsRunning()) {
        MainManager::HandEvent(&SDLEvent);
        MainManager::Update();
        MainManager::Rander();
    }
    return 0;
}

void MainManager::HandEvent(SDL_Event *Event)  {
    while (SDL_PollEvent(Event)) {
        switch (Event->type) {
        case SDL_QUIT:
            spdlog::info("SDL_QUIT event received. Exiting main loop.");
            MainManager::Shutdown();
            break;
        default:
            if (CurrentScene)
                CurrentScene->HandleEvents(Event);
            else
                spdlog::warn("No CurrentScene to handle events.");
            break;
        }
    }
}

void MainManager::Update() {
    if (CurrentScene) {
        CurrentScene->Update();
    } else {
        SDL_Delay(1); // yield CPU when no scene is set
    }
}

void MainManager::Rander() {
    SDL_RenderClear(SDLRenderer);
    if (CurrentScene)
        CurrentScene->Render();
    else
        spdlog::warn("No CurrentScene to render.");
    SDL_RenderPresent(SDLRenderer);
}



void MainManager::Shutdown() {
    if (GetIsRunning()) {
        spdlog::info("Application Shutting Down.");
        SetIsRunning(false);
    }
}

void MainManager::AssertionFailure(bool Condition, const char* Message) {
    if (Condition) 
        spdlog::info("Assertion passed. {} loaded successfully.", Message);
    else 
        spdlog::error("Assertion failed! {} failed to load.", Message);
}