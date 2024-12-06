#pragma once
#include "../game.h"
#include <SDL2/SDL.h>

class Scene {
public:
    virtual ~Scene() { }
    virtual void Load() = 0;     // シーンの初期化
    virtual void ProcessInput(); // 入力判定
    virtual void Update() = 0;   // 更新処理
    virtual void Draw()   = 0;   // 描画処理
    virtual void Unload() = 0;   // リソースの解放
protected:
    Game* mGame;
};