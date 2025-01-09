#include "riderMove.h"
#include <iostream>

RiderMove::RiderMove(GameObject* owner)
    : Behaviour(owner)
{
    // std::cout << "riderMove constructor" << std::endl;
}

void RiderMove::Start()
{
    // std::cout << "riderMove start" << std::endl;
    dir_x = 0.0f;
    dir_y = 0.0f;
}
namespace {

}
void RiderMove::Update()
{
    // bool isMove = false;
    // dir_x       = 0.0f;
    // dir_y       = 0.0f;
    // if (Input::GetKey(SDL_SCANCODE_W) && !Input::GetKey(SDL_SCANCODE_S)) {
    //     dir_y -= 1.0f;
    //     isMove = true;
    // }
    // if (Input::GetKey(SDL_SCANCODE_S) && !Input::GetKey(SDL_SCANCODE_W)) {
    //     dir_y += 1.0f;
    //     isMove = true;
    // }
    // if (Input::GetKey(SDL_SCANCODE_A) && !Input::GetKey(SDL_SCANCODE_D)) {
    //     dir_x -= 1.0f;
    //     isMove = true;
    // }
    // if (Input::GetKey(SDL_SCANCODE_D) && !Input::GetKey(SDL_SCANCODE_A)) {
    //     dir_x += 1.0f;
    //     isMove = true;
    // }

    // if (isMove) {
    //     float angle = Math::Atan2(dir_y, dir_x);
    //     Vector3 axis(0.0f, 1.0f, 0.0f);
    //     Quaternion q(axis, angle - Math::PiOver2);
    //     mOwner->GetTransform()->SetWorldRotation(q);
    // }
}
void RiderMove::LateUpdate()
{
}
