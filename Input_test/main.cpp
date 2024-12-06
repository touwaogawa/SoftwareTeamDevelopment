#include "input.h"
#include <SDL2/SDL.h>
#include <iostream>

int main(int argc, char* argv[])
{
    // SDLの初期化
    SDL_Init(SDL_INIT_VIDEO);
    // インスタンス化
    Input& input = Input::GetInstance();

    bool frag = true;
    while (frag) {
        input.ProcessInput(); // 全ての入力の状態を更新

        if (input.GetKey(KeyCode::ESCAPE)) {
            frag = false;
        }
        if (input.GetKey(KeyCode::SPACE)) {
            if (input.ConnectController()) {
                std::cout << "接続成功" << std::endl;
            } else {
                std::cout << "接続失敗" << std::endl;
            }
        }
    }

    return 0;
}