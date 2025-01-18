#pragma once
#include "../../../../../utils/src/math.h"
#include "../../../component/behaviour.h"
#include <reactphysics3d/reactphysics3d.h>
#include <string>

class Hero;
class HitBox;
class HitBoxMove : public Behaviour {
public:
    explicit HitBoxMove(Hero* ownerHero, HitBox* owner, const std::string& ignoreTag, Vector3 hitVector, float damage, int destrpyFrame, int& actionFrame);
    virtual ~HitBoxMove() override = default;

    void Update() override;

    void OnOverlapEnter(const rp3d::Collider* self, const rp3d::Collider* opponent, const rp3d::OverlapCallback::OverlapPair& pair) override;

private:
    Hero* mOwnerHero;
    HitBox* const mHitBox;
    const std::string mIgnoreTag;
    const Vector3 mHitVector;
    const float mDamage;
    const int mDestroyFrame;
    const int& mActionFrame;
    int mPreActionFrame;
    bool mIsDeatroy;
};