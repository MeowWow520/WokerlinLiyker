#include "SceneMainTitle.h"



SceneMainTitle::SceneMainTitle() {}

SceneMainTitle::~SceneMainTitle() {}

void SceneMainTitle::Init() {

    PlayerInstance.Texture = IMG_LoadTexture(
        MainManager::Instance()->GetSDLRenderer(), "../../assists/CatPackFree/CatPackFree/Idle.png");
    SDL_QueryTexture(PlayerInstance.Texture, NULL, NULL, &PlayerInstance.Width, &PlayerInstance.Height);
}

void SceneMainTitle::HandleEvents(SDL_Event* Event) {
}

void SceneMainTitle::Update() {
}

void SceneMainTitle::Clean() {
}

void SceneMainTitle::Render() {
}
