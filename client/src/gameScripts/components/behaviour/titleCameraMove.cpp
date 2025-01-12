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
    transform->SetWorldPosition(Vector3(0.0f, 40.0f, -40.0f));
    Matrix4 view = Matrix4::CreateLookAt(transform->GetWorldPosition(), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f));

    transform->SetWorldMatrix(view);
    Audio::FadeInMusic("../assets/sounds/bgm/Who_Is_the_Champion.mp3", 1000);
    // Audio::PlayMusic("../assets/sounds/bgm/Who_Is_the_Champion.mp3");
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

    Matrix4 view = Matrix4::CreateLookAt(transform->GetWorldPosition(), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f));

    transform->SetWorldMatrix(view);
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