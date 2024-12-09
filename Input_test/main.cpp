#include "input.h"
#include <SDL2/SDL.h>
#include <iostream>

int main(int argc, char* argv[])
{
    // SDLの初期化
    SDL_Init(SDL_INIT_VIDEO);


    if (Input::ConnectController()) {
        std::cout << "接続成功" << std::endl;
    } else {
        std::cout << "接続失敗" << std::endl;
        return 0;
    }
    bool frag = true;
    while (frag) {
        Input::ProcessInput(); // 全ての入力の状態を更新

        if (Input::GetKey(SDLK_a)) {
            frag = false;
        }
        if (Input::GetKey(SDLK_b)) {
            std::cout << "key b" << std::endl;
        }
        if(Input::GetButtonDown("A")){
            std::cout << "button a" << std::endl;
        }
        if(Input::GetButton("X")){
            std::cout << "button x" << std::endl;
        }
        if(Input::GetButtonUp("B")){
            std::cout << "button b" << std::endl;
            frag = false;
        }
        if(Input::GetButtonDown("Home")){
            std::cout << "buttonHome" << std::endl;
        }
        if(Input::GetAxis("JcRStickX")){
            std::cout << "スティックｘ" << std::endl;
        }
    }
    Input::ShutDown();

    return 0;
}