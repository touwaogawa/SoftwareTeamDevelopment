#include "riderMove.h"
#include "../../../../../utils/src/math.h"
#include "../../../component/transform.h"
#include "../../gameObject/rider.h"
#include <iostream>

RiderMove::RiderMove(GameObject* owner)
    : Behaviour(owner)
{
    // std::cout << "riderMove constructor" << std::endl;
    mRider = static_cast<Rider*>(mOwner);
}

void RiderMove::Start()
{
    // std::cout << "riderMove start" << std::endl;
    dir_x = 0.0f;
    dir_y = 0.0f;
}
namespace {
void show(Transform* transform)
{
    std::cout << "rider move" << std::endl;
    Quaternion wq = transform->GetWorldRotation();
    std::cout << " wqx:" << wq.x << " wqy:" << wq.y << " wqz:" << wq.z << " wqw:" << wq.w << std::endl;
    Quaternion lq = transform->GetLocalRotation();
    std::cout << " lqx:" << lq.x << " lqy:" << lq.y << " lqz:" << lq.z << " lqw:" << lq.w << std::endl;
    Vector3 wpos = transform->GetWorldPosition();
    std::cout << " wposx:" << wpos.x << " wposy:" << wpos.y << " wposz:" << wpos.z << std::endl;
    Vector3 lpos = transform->GetLocalPosition();
    std::cout << " lposx:" << lpos.x << " lposy:" << lpos.y << " lposz:" << lpos.z << std::endl;
    Vector3 wscale = transform->GetWorldScale();
    std::cout << " wscalex:" << wscale.x << " wscaley:" << wscale.y << " wscalez:" << wscale.z << std::endl;
    Vector3 lscale = transform->GetLocalScale();
    std::cout << " lscalex:" << lscale.x << " lscaley:" << lscale.y << " lscalez:" << lscale.z << std::endl;
    if (transform->GetParent() == nullptr)
        std::cout << "noparent" << std::endl;
}
}
void RiderMove::Update()
{
    // show(mRider->GetTransform());
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
