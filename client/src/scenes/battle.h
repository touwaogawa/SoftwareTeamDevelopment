#pragma once
#include "../gameScripts/hero/hero.h"
#include "../scene.h"

class BattleScene : public Scene {
public:
    BattleScene();
    ~BattleScene() override;
    bool Load() override;

private:
    class GameObject* mHelo;
    class GameObject* mStage;
};