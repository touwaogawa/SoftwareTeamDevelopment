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

private:
    class Hero* mHero;
    int mCurrentActionFrame;
    rp3d::RigidBody* mHeroRp3dRigidBody;
};