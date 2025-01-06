#include "heroMove.h"
#include "../../../../../utils/src/math.h"
#include "../../../component/rigidBody.h"
#include "../../../component/transform.h"
#include "../../gameObject/hero.h"
#include <iostream>
HeroMove::HeroMove(GameObject* owner)
    : Behaviour(owner)
{
    std::cout << "heroMove constructer" << std::endl;
}

void HeroMove::Start()
{
    std::cout << "heroMove start" << std::endl;
    mHero        = static_cast<Hero*>(mOwner);
    RigidBody* r = mOwner->GetComponent<RigidBody>();
    if (r) {
        r->SetTransform();
    }
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
    // show(mOwner->GetTransform());
    UpdatePosision();
}
void HeroMove::LateUpdate()
{
}

// ##############################################
void HeroMove::Walking(Vector2 axis)
{
    mHero->mCurrentStatus.moveDir = Vector2::Normalize(axis);
    if (mHero->mCurrentStatus.speed < mHero->GetMaxWalkSpeed()) {
        mHero->mCurrentStatus.speed = std::min(mHero->GetMaxWalkSpeed(), mHero->mCurrentStatus.speed + mHero->GetWalkAcceleration());
    }
}
void HeroMove::StartRunning(Vector2 axis)
{
    mHero->mCurrentStatus.moveDir = Vector2::Normalize(axis);
    mHero->mCurrentStatus.speed   = std::min(mHero->GetMaxRunSpeed(), mHero->mCurrentStatus.speed + mHero->GetDushAcceleration());
}
void HeroMove::Running(Vector2 axis)
{
    mHero->mCurrentStatus.moveDir = Vector2::Normalize(axis);
}
void HeroMove::StopRunning(Vector2 axis)
{
    if (mHero->mCurrentStatus.speed < 0.05f) {
        mHero->mCurrentStatus.speed = 0.0f;
    } else {
        mHero->mCurrentStatus.speed -= mHero->GetTraction() * mHero->GetGravity();
        if (mHero->mCurrentStatus.speed < 0.0f) {
            mHero->mCurrentStatus.speed = 0.0f;
        }
    }
}
void HeroMove::StartRunningAttack(Vector2 axis)
{
    mCurrentActionFrame         = 0;
    mHero->mCurrentStatus.speed = 1.0f;
}
bool HeroMove::UpdateRunningAttack()
{
    mCurrentActionFrame++;
    if (10 <= mCurrentActionFrame) {
        mHero->mCurrentStatus.speed -= 0.5f;
        if (mHero->mCurrentStatus.speed < 0.05) {
            mHero->mCurrentStatus.speed = 0.0f;
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
    Vector2 ma = mHero->mCurrentStatus.moveDir;
    float cs   = mHero->mCurrentStatus.speed;
    // std::cout << "cs " << cs << std::endl;
    std::cout << "ma_x " << ma.x << std::endl;
    std::cout << "ma_y " << ma.y << std::endl;
    pos.x += cs * ma.x;
    pos.z += cs * ma.y;
    // mOwner->GetTransform()->SetLocalPosition(pos);
    RigidBody* r = mOwner->GetComponent<RigidBody>();
    if (r) {
        r->SetVA(ma.x * 5.0f, 0.0f, ma.y * 5.0f);
    }
}