#include "titleCameraMove.h"
#include "../../../../../common/src/component/transform.h"
#include "../../../../../common/src/gameObject.h"
#include "../../../component/camera.h"
#include <iostream>

TitleCameraMove::TitleCameraMove(GameObject* owner)
    : Behaviour(owner)
{
}

void TitleCameraMove::Start()
{
    mOwner->GetTransform()->SetWorldPosition(Vector3(0.0f, 40.0f, -40.0f));
    mAngle = 0.0f;
}
void TitleCameraMove::Update()
{
    float r = 40.0f;
    float x = r * Math::Cos(mAngle);
    float z = r * Math::Sin(mAngle);
    mAngle += Math::ToRadians(1.0f);
    Transform* transform = mOwner->GetTransform();
    transform->SetWorldPosition(Vector3(x, 40.0f, z));

    Matrix4 view = Matrix4::CreateLookAt(transform->GetWorldPosition(), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f));

    transform->SetWorldMatrix(view);
}
void TitleCameraMove::LateUpdate() { }