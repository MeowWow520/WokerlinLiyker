#define SDL_MAIN_HANDLED
#define _CRT_SECURE_NO_WARNINGS
#include "Manager/MainManager.h"



int main(int argc, char** argv) 
{
    return MainManager::Instance()->RunApplication(argc, argv);
}