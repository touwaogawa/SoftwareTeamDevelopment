#pragma once
#include "../gameScripts/hero/hero.h"
#include "../scene.h"

class BattleScene : public Scene {
public:
    BattleScene();
    ~BattleScene() override;
    bool Load() override;
    bool ProccessInput() override;

    class Stage* GetStage() const;

private:
    class Player* mPlayer;
    class Stage* mStage;
};