#pragma once
#include "scene.h"
#include <SDL2/SDL.h>

class TitleScene : public Scene {
public:
    TitleScene();
    ~TitleScene();

    void Load() override;         // 初期化
    void ProcessInput() override; // 入力判定
    void Update() override;       // 更新
    void Draw() override;         // 描画
    void Unload() override;       // リソース解放
private:
};