#pragma once
#include "../../../../../utils/src/math.h"
#include "../../../component/behaviour.h"
#include <reactphysics3d/reactphysics3d.h>

class Vector2;
class Hero;
class HeroMove : public Behaviour {
public:
    explicit HeroMove(Hero* owner);
    virtual ~HeroMove() override = default;

    void Start() override;
    void Update() override;
    void LateUpdate() override;

    void OnCollisionEnter(const rp3d::Collider* self, const rp3d::Collider* opponent, const rp3d::CollisionCallback::ContactPair& pair) override;
    void OnCollisionExit(const rp3d::Collider* self, const rp3d::Collider* opponent, const rp3d::CollisionCallback::ContactPair& pair) override;

    void OnOverlapEnter(const rp3d::Collider* self, const rp3d::Collider* opponent, const rp3d::OverlapCallback::OverlapPair& pair) override;
    void OnOverlapExit(const rp3d::Collider* self, const rp3d::Collider* opponent, const rp3d::OverlapCallback::OverlapPair& pair) override;

    virtual void OnDamage(int stopFrame, int downFrame, rp3d::Vector3 vector);
    virtual void HitOther(int stopFrame, float power);

private:
    Hero* const mHero;
    rp3d::RigidBody* mHeroRp3dRigidBody;
    rp3d::Vector3 mKnockBackVectorBuffer;
};