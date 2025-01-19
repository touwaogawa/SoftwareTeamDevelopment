#pragma once
#include "../../../../../../common/src/component/behaviour.h"

class Hero;
class FaceDirMove : public Behaviour {
public:
    explicit FaceDirMove(GameObject* owner, Hero* hero);
    virtual ~FaceDirMove() override = default;

    void Start() override;
    void Update() override;

private:
    Hero* mHero;
};