#pragma once
#include "../../../../../common/src/component/behaviour.h"
#include <vector>

class Hero;
class BattleCameraMove : public Behaviour {
public:
    explicit BattleCameraMove(GameObject* owner);
    ~BattleCameraMove() override = default;

    void Start() override;
    void Update() override;
    void LateUpdate() override;

    void AddHero(Hero* hero) { mAliiveHeroes.push_back(hero); }
    void RemoveHero(Hero* hero);

    // void Awake() override;
    // void OnEnable() override;

private:
    std::vector<Hero*> mAliiveHeroes;
    float mMaxFromCenter;
};