#include "titleCameraMove.h"
#include "../../../../../common/src/component/transform.h"
#include "../../../../../common/src/gameObject.h"
#include "../../../audio.h"
// #include "../../../component/cameraComponent.h"
#include <iostream>

TitleCameraMove::TitleCameraMove(GameObject* owner)
    : Behaviour(owner)
    , mAngle(0.0f)
{
}

void TitleCameraMove::Start()
{
    Transform* transform = mOwner->GetTransform();
    transform->SetWorldPosition(Vector3(0.0f, 35.0f, -40.0f));

    Audio::SetMusicVolume(0.4);
    Audio::FadeInMusic("../assets/sounds/bgm/Who_Is_the_Champion.mp3", 1000);
}
void TitleCameraMove::Update()
{
    // std::cout << "update" << std::endl;
    float r = 40.0f;
    float x = r * Math::Cos(mAngle);
    float z = r * Math::Sin(mAngle);
    mAngle += Math::ToRadians(0.5f);
    Transform* transform = mOwner->GetTransform();
    transform->SetWorldPosition(Vector3(x, 40.0f, z));
}
void TitleCameraMove::LateUpdate() { }
// void TitleCameraMove::Awake()
// {
//     std::cout << "awake" << std::endl;
// }
// void TitleCameraMove::OnEnable()
// {
//     std::cout << "OneEnable" << std::endl;
// }