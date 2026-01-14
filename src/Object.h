#pragma once 

#ifndef OBJECT_H
#define OBJECT_H
#include <SDL.h>



struct Player {
    SDL_Texture* Texture = nullptr;
    SDL_FPoint Position = { 0,0 };
    int Width{0}, Height{0};
};

#endif //!OBJECT_H