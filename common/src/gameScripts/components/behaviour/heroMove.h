#pragma once
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

    void OnDamage(int stopFrame, float damage, Vector3 vector);

    void OnCollisionEnter(const rp3d::Collider* self, const rp3d::Collider* opponent, const rp3d::CollisionCallback::ContactPair& pair) override;

    void OnOverlapEnter(const rp3d::Collider* self, const rp3d::Collider* opponent, const rp3d::OverlapCallback::OverlapPair& pair) override;

private:
    Hero* mHero;
    rp3d::RigidBody* mHeroRp3dRigidBody;
};