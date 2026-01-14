#pragma once

#ifndef SCENEMAINTITLE_H
#define SCENEMAINTITLE_H
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <spdlog/spdlog.h>
#include "SceneBaseClass.h"
#include "../Manager/MainManager.h"
#include "../Object.h"



class SceneMainTitle : public SceneBaseClass {

public:
    SceneMainTitle();
    ~SceneMainTitle() override;
    void Init() override;
    void HandleEvents(SDL_Event* Event) override;
    void Update() override;
    void Render() override; 
    void Clean() override;

private:
    Player PlayerInstance;
};

#endif // !SCENEMAINTITLE_H