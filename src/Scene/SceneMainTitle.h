#pragma once

#ifndef SCENEMAINTITLE_H
#define SCENEMAINTITLE_H
#include <SDL.h>
#include "SceneBaseClass.h"


class SceneMainTitle : public SceneBaseClass {

public:
    SceneMainTitle();
    ~SceneMainTitle() override;
    void Init() override;
    void HandleEvents(SDL_Event* Event) override;
    void Update() override;
    void Render() override; 
    void Clean() override;
};
#endif // !SCENEMAINTITLE_H