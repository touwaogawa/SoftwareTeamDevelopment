#include "heroMove.h"
#include "../../../../client/src/beySmashEngine.h"
#include "../../../../client/src/scenes/battle.h"
#include "../stage/stage.h"
#include "hero.h"

HeroMove::HeroMove(GameObject* owner)
    : Behaviour(owner)
{
}

void HeroMove::Start()
{
    mBattleScene = static_cast<BattleScene*>(mOwner->GetScene());
    mHero        = static_cast<Hero*>(mOwner);
    mGravity     = mBattleScene->GetStage()->GetGravity();
}
namespace {
// デバッグ用
void show(Transform* transform)
{
    std::cout << "heromove" << std::endl;
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
void HeroMove::Update()
{
    UpdatePosision();
}
void HeroMove::LateUpdate()
{
}

// ##############################################
void HeroMove::Walking(Vector2 axis)
{
    mHero->currentMoveAxis = Vector2::Normalize(axis);
    if (mHero->currentSpeed < mHero->GetMaxWalkSpeed()) {
        mHero->currentSpeed = std::min(mHero->GetMaxWalkSpeed(), mHero->currentSpeed + mHero->GetWalkAcceleration());
    }
}
void HeroMove::StartRunning(Vector2 axis)
{
    mHero->currentMoveAxis = Vector2::Normalize(axis);
    mHero->currentSpeed    = std::min(mHero->GetMaxRunSpeed(), mHero->currentSpeed + mHero->GetDushAcceleration());
}
void HeroMove::Running(Vector2 axis)
{
    mHero->currentMoveAxis = Vector2::Normalize(axis);
}
void HeroMove::StopRunning(Vector2 axis)
{
    if (mHero->currentSpeed < 0.05f) {
        mHero->currentSpeed = 0.0f;
    } else {
        mHero->currentSpeed -= mHero->GetTraction() * mGravity;
        if (mHero->currentSpeed < 0.0f) {
            mHero->currentSpeed = 0.0f;
        }
    }
}
void HeroMove::StartRunningAttack(Vector2 axis)
{
    mCurrentActionFrame = 0;
    mHero->currentSpeed = 1.0f;
}
bool HeroMove::UpdateRunningAttack()
{
    mCurrentActionFrame++;
    if (10 <= mCurrentActionFrame) {
        mHero->currentSpeed -= 0.5f;
        if (mHero->currentSpeed < 0.05) {
            mHero->currentSpeed = 0.0f;
            return false;
        }
    }
    return true;
}
void HeroMove::UpdatePosision()
{
    Vector3 pos = mOwner->GetTransform()->GetLocalPosition();
    // std::cout << "pos_x: " << pos.x << std::endl;
    // std::cout << "pos_z: " << pos.z << std::endl;
    Vector2 ma = mHero->currentMoveAxis;
    float cs   = mHero->currentSpeed;
    // std::cout << "cs " << cs << std::endl;
    // std::cout << "ma_x " << ma.x << std::endl;
    // std::cout << "ma_x " << ma.y << std::endl;
    pos.x += cs * ma.x;
    pos.z += cs * ma.y;
    mOwner->GetTransform()->SetLocalPosition(pos);
}