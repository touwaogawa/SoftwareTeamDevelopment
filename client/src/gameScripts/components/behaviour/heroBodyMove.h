#pragma once
#include "../../../../../common/src/component/behaviour.h"

class HeroBody;
class Hero;
class HeroBodyMove : public Behaviour {
public:
    explicit HeroBodyMove(HeroBody* owner, Hero* hero);
    virtual ~HeroBodyMove() override = default;

    void Start() override;
    void Update() override;
    void LateUpdate() override;

private:
    HeroBody* const mHeroBody;
    Hero* const mHero;
};