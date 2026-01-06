#include "MainManager.h"



MainManager::MainManager() {
    SetLoggerLevel(spdlog::level::info);
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
    (void)argc;
    (void)argv;
    // Main application loop
    spdlog::info("Application Started.");
    while (GetIsRunning()) {
        MainManager::SDLPullEvents(SDLEvent);
        
    }
    return 0;
}

void MainManager::Shutdown() {
    if (GetIsRunning()) {
        spdlog::info("Application Shutting Down.");
        IsRunning = false;
    }
}

bool MainManager::SetLoggerLevel(spdlog::level::level_enum level) {
    try {
        spdlog::set_level(level);
        return true;
    } catch (const spdlog::spdlog_ex& ex) {
        spdlog::error("Log level set failed: {}", ex.what());
        return false;
    }
}

void MainManager::AssertionFailure(bool Condition, const char* Message) {
    if (Condition) 
        spdlog::info("Assertion passed. {} loaded successfully.", Message);
    else 
        spdlog::error("Assertion failed! {} failed to load.", Message);
}

void MainManager::PrintPrivateVariables() const {
    spdlog::trace("IsRunning: {}", IsRunning);
    spdlog::trace("WindowWidth: {}", WindowWidth);
    spdlog::trace("WindowHeight: {}", WindowHeight);
    spdlog::trace("IsPrintMouseMove: {}", IsPrintMouseMove);
}

void MainManager::SDLPullEvents(SDL_Event& Event) {
    while (SDL_PollEvent(&Event)) {
        switch (Event.type) {
        case SDL_QUIT:
            spdlog::info("SDL_QUIT event received. Exiting main loop.");
            SetIsRunning(false);
            break;
        case SDL_MOUSEMOTION:
            PosCursor.x = Event.motion.x;
            PosCursor.y = Event.motion.y;
            if (IsPrintMouseMove)
                spdlog::trace("Mouse moved to ({}, {})", Event.motion.x, Event.motion.y);
            break;
        default:
            break;
        }
    }
}
