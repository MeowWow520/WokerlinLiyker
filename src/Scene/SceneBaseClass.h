#pragma once

#ifndef SCENEBASECLASS_H
#define SCENEBASECLASS_H
#include <SDL.h>


class SceneBaseClass {
public:
    // 纯虚函数，派生类必须实现这些方法
    SceneBaseClass() = default;
    virtual ~SceneBaseClass() = default;
    /** 初始化场景
     * 
     */
    virtual void Init() = 0;
    virtual void HandleEvents(SDL_Event* Event) = 0;
    virtual void Update() = 0;
    virtual void Render() = 0; 
    virtual void Clean() = 0;
};

#endif // !SCENEBASECLASS_H