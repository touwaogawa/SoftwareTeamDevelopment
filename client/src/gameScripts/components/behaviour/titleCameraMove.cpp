#include "titleCameraMove.h"
#include "../../../../../common/src/component/transform.h"
#include "../../../../../common/src/gameObject.h"
#include "../../../../../common/src/scene.h"
#include "../../../../../common/src/sceneManager.h"
#include "../../../../../utils/src/math.h"
#include "../../../audio.h"
#include "../../../component/cameraComponent.h"
#include <iostream>

TitleCameraMove::TitleCameraMove(GameObject* owner, CameraComponent* camera)
    : Behaviour(owner)
    , mAngle(0.0f)
    , mCurrentframe(SceneManager::GetCurrentScene()->currentFrame)
    , mCamera(camera)
{
}

void TitleCameraMove::Start()
{

    Audio::SetMusicVolume(0.4);
    Audio::FadeInMusic("../assets/sounds/bgm/Who_Is_the_Champion.mp3", 1000);
    mCamera->SetUseTarget(false);
}
void TitleCameraMove::Update()
{
    // std::cout << "update" << std::endl;
    if (mCurrentframe == 0) {
        mCamera->SetUseTarget(false);
        // GetTransform()->SetWorldRotation(Quaternion(Vector3(0.0f, 1.0f, 0.0f), 0));
        GetTransform()->SetWorldPosition(Vector3(-3.0f, 2.0f, -3.0f));

    } else if (mCurrentframe < 60 * 7) {
        Vector3 pos = Vector3::Lerp(Vector3(-2.0f, 2.0f, -3.0f), Vector3(2.0f, 2.0f, -3.0f), (mCurrentframe / static_cast<float>(60 * 7)));
        GetTransform()->SetWorldPosition(pos);

    } else if (mCurrentframe == 60 * 7) {
        // GetTransform()->SetWorldRotation(Quaternion(Vector3(0.0f, 1.0f, 0.0f), Math::Pi));

    } else if (mCurrentframe < 60 * 14) {
        Vector3 pos = Vector3::Lerp(Vector3(-4.0f, -10.0f, -80.0f), Vector3(4.0f, -3.0f, -80.0f), ((mCurrentframe - 60 * 7) / static_cast<float>(60 * 7)));
        GetTransform()->SetWorldPosition(pos);

    } else if (mCurrentframe == 60 * 14) {
        mCamera->SetUseTarget(true);
        mCamera->SetTarget(Vector3(0.0f, 2.0f, 0.0f));

        GetTransform()->SetWorldPosition(Vector3(0.0f, -3.0f, 24.0f));
    } else if (mCurrentframe < 60 * 21) {
        Vector3 cpos       = GetTransform()->GetWorldPosition();
        Vector3 nextpos_xz = Vector3::Transform(cpos, Quaternion(Vector3::UnitY, Math::ToRadians(-3.0f)));
        Vector3 nextpos    = Vector3(nextpos_xz.x, nextpos_xz.y + 0.1f, nextpos_xz.z);
        GetTransform()->SetWorldPosition(nextpos);

    } else if (mCurrentframe == 60 * 21) {

    } else if (mCurrentframe < 60 * 23) {
        Vector3 cpos       = GetTransform()->GetWorldPosition();
        Vector3 nextpos_xz = Vector3::Transform(cpos, Quaternion(Vector3::UnitY, Math::ToRadians(-3.0f)));
        nextpos_xz *= 0.96f;
        Vector3 nextpos = Vector3(nextpos_xz.x, nextpos_xz.y + 0.1f, nextpos_xz.z);
        GetTransform()->SetWorldPosition(nextpos);

    } else {

        float r = 40.0f;
        float x = r * Math::Cos(mAngle);
        float z = r * Math::Sin(mAngle);
        mAngle += Math::ToRadians(0.5f);
        Transform* transform = mOwner->GetTransform();
        transform->SetWorldPosition(Vector3(x, 40.0f, z));
    }
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