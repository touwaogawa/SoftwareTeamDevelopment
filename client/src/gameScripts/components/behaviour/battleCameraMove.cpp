#include "battleCameraMove.h"
#include "../../../../../common/src/component/transform.h"
#include "../../../../../common/src/gameObject.h"
#include "../../../../../common/src/gameScripts/gameObject/hero.h"
#include "../../../../../common/src/gameScripts/gameObject/player.h"
#include "../../../../../utils/src/math.h"
#include "../../../component/cameraComponent.h"
#include "../../../renderer.h"
#include "../../scene/battle.h"
#include <vector>

BattleCameraMove::BattleCameraMove(GameObject* owner)
    : Behaviour(owner)
    , mMaxFromCenter(5.0f)
{
}

void BattleCameraMove::Start()
{
}
void BattleCameraMove::Update()
{
    for (Hero* hero : mAliiveHeroes) {
        if (hero->mCurrentStatus.state == HeroState::Death) {
            RemoveHero(hero);
        }
    }
}
void BattleCameraMove::LateUpdate()
{
    if (mAliiveHeroes.size() > 0) {

        // 全プレイヤーの重心
        Vector3 centerPos(0.0f, 0.0f, 0.0f);
        int num = 0;
        for (Hero* hero : mAliiveHeroes) {
            centerPos += hero->GetTransform()->GetWorldPosition();
            num++;
        }
        // y軸の追従は減らす
        centerPos.y *= 0.3f;
        if (num > 0) {
            centerPos.x /= num;
            centerPos.y /= num;
            centerPos.z /= num;
        }

        centerPos.y += 3.0f;

        float maxDistance = 0.0f;

        for (size_t i = 0; i < mAliiveHeroes.size(); ++i) {
            for (size_t j = i + 1; j < mAliiveHeroes.size(); ++j) {
                Vector3 buf    = mAliiveHeroes[i]->GetTransform()->GetWorldPosition() - mAliiveHeroes[j]->GetTransform()->GetWorldPosition();
                float distance = buf.Length();
                maxDistance    = Math::Max(maxDistance, distance);
            }
        }

        float fov = 26.f + (maxDistance - 9.0f) * 0.7f;

        CameraComponent* cc = mOwner->GetComponent<CameraComponent>();
        if (cc) {
            Matrix4 proj = Matrix4::CreatePerspectiveFOV(Math::ToRadians(fov), Renderer::GetWindowWidth(), Renderer::GetWindowHeight(), 1.0f, 150.0f);
            cc->SetProjection(proj);
        }
        Vector3 vecFromCenter = centerPos - Vector3(0.0f, 0.0f, 0.0f);
        Vector3 targetpos; // 正中線
        if (vecFromCenter.Length() > mMaxFromCenter) {
            // 重心が範囲外
            targetpos = mMaxFromCenter * Vector3::Normalize(vecFromCenter);
        } else {
            // 重心が範囲内
            targetpos = centerPos;
        }
        cc->SetTarget(targetpos);
    } else {
        CameraComponent* cc = mOwner->GetComponent<CameraComponent>();
        Matrix4 proj        = Matrix4::CreatePerspectiveFOV(Math::ToRadians(40.0f), Renderer::GetWindowWidth(), Renderer::GetWindowHeight(), 1.0f, 150.0f);
        cc->SetProjection(proj);

        cc->SetTarget(Vector3(0.0f, 0.0f, 0.0f));
    }
}

void BattleCameraMove::RemoveHero(Hero* hero)
{
    auto end = std::remove(mAliiveHeroes.begin(), mAliiveHeroes.end(), hero);
    mAliiveHeroes.erase(end, mAliiveHeroes.end());
}