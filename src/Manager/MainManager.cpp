#include "MainManager.h"



MainManager::MainManager() {
    SetLoggerLevel(spdlog::level::warn);
    spdlog::info("MainManager initialized.");
}

MainManager::~MainManager() {
    spdlog::info("MainManager destroyed.");
}

int MainManager::RunApplication(int argc, char** argv) {
    (void)argc;
    (void)argv;
    spdlog::info("Application Started.");
    // Main application loop
    return 0;
}

void MainManager::Shutdown() {
    spdlog::info("Application Shutting Down.");
    IsRunning = false;
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