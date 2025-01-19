#include "hitBoxMove.h"
#include "../../../../../common/src/component/rigidBody.h"
#include "../../../../../common/src/component/transform.h"
#include "../../../../../utils/src/math.h"
#include "../../gameObject/hero.h"
#include "../../gameObject/hitBox.h"
#include "heroMove.h"
#include <iostream>
HitBoxMove::HitBoxMove(Hero* ownerHero, HitBox* owner, const std::string& ignoreTag, Vector3 hitVector, float damage, int destrpyFrame, int& actionFrame)
    : Behaviour(owner)
    , mOwnerHero(ownerHero)
    , mHitBox(owner)
    , mIgnoreTag(ignoreTag)
    , mHitVector(hitVector)
    , mDamage(damage)
    , mDestroyFrame(destrpyFrame)
    , mActionFrame(actionFrame)
    , mPreActionFrame(0)
    , mIsDeatroy(false)
{
    // std::cout << "HitBoxMove constructor" << std::endl;
}

void HitBoxMove::Update()
{
    if (mActionFrame == mDestroyFrame || mPreActionFrame > mActionFrame) {
        if (!mIsDeatroy) {
            // std::cout << "hitboc destroy" << std::endl;
            mHitBox->Destroy();
            mIsDeatroy = true;
        }
    }
    mPreActionFrame = mActionFrame;
}

void HitBoxMove::OnOverlapEnter(const rp3d::Collider* self, const rp3d::Collider* opponent, const rp3d::OverlapCallback::OverlapPair& pair)
{
    GameObject* op = static_cast<GameObject*>(opponent->getBody()->getUserData());
    if (op->GetName() == "Hero" && op->GetTag() != mIgnoreTag) {
        // 敵のしょり
        Hero* hero = static_cast<Hero*>(op);
        if (hero->mCurrentStatus.state == HeroState::KnockBack) {
            return;
        }
        // std::cout << "hit" << std::endl;

        HeroMove* heroMove = static_cast<HeroMove*>(hero->GetBehaviour());

        int knockbackTime = static_cast<int>(10 + (10 * (hero->mCurrentStatus.damageSum * 0.01f)));

        rp3d::Vector3 hitVector(mHitVector.x, mHitVector.y, mHitVector.z);
        hitVector *= (1.0f + hero->mCurrentStatus.damageSum * 0.01f);
        int stopFrame = static_cast<int>(10 + Math::Clamp(static_cast<int>(hitVector.length() * 0.05), 0, 50));
        heroMove->OnDamage(mDamage, stopFrame, knockbackTime, hitVector);

        // 自分の処理
        HeroMove* ownerHeroMove = static_cast<HeroMove*>(mOwnerHero->GetBehaviour());
        ownerHeroMove->HitOther(stopFrame);
    }
}
