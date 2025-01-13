#pragma once
#include "../../../component/behaviour.h"
#include <reactphysics3d/reactphysics3d.h>

class Vector2;
class HeroMove : public Behaviour {
public:
    explicit HeroMove(GameObject* owner);
    ~HeroMove() override = default;

    void Start() override;
    void Update() override;
    void LateUpdate() override;

    void OnCollisionEnter(const rp3d::Collider* self, const rp3d::Collider* opponent, const rp3d::CollisionCallback::ContactPair& pair) override;

    void OnOverlapEnter(const rp3d::Collider* self, const rp3d::Collider* opponent, const rp3d::OverlapCallback::OverlapPair& pair) override;

private:
    class Hero* mHero;
    int mCurrentActionFrame;
    rp3d::RigidBody* mHeroRp3dRigidBody;
};