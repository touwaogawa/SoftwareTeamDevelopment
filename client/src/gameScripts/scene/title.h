#pragma once
#include "../../../../common/src/scene.h"
#include <vector>

class TitleScene : public Scene {
public:
    TitleScene();
    ~TitleScene() override = default;
    bool Load() override;
    void Update(bool& exitFrag, float timeStep) override;

private:
    bool ProccessInput();
    class Player_C* mPlayer;
};