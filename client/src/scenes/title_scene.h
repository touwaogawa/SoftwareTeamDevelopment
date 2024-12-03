#pragma once
#include "scene.h"
#include <SDL2/SDL.h>

class TitleScene : public Scene {
public:
    TitleScene();
    ~TitleScene();

    void Load() override;                                   // 初期化
    void Update() override;                                 // 更新
    void GenerateOutput(class Renderer* renderer) override; // 描画
    void Unload() override;                                 // リソース解放

    void ProcessInput(SDL_Event& event); // ユーザー入力処理
private:
    SDL_Texture* mTitleTexture; // タイトルテキスト用のテクスチャ
    SDL_Rect mTitleRect;        // テクスチャの描画位置
    SDL_Renderer* mRenderer;    // レンダラー
};