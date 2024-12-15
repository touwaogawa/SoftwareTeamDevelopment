#pragma once
#include "../Scene.h"
#include "../gameScripts/hero/hero.h"

class BattleScene : public Scene {
public:
    BattleScene();
    ~BattleScene() override;
    bool Load() override;

private:
    class GameObject* mHelo;
    class GameObject* mStage;
};