#pragma once
#include "../gameScripts/hero/hero.h"
#include "../scene.h"

class BattleScene : public Scene {
public:
    BattleScene();
    ~BattleScene() override;
    bool Load() override;
    bool ProccessInput() override;

private:
    class Player* mPlayer;
    class GameObject* mStage;
};