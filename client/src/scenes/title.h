#pragma once
#include "../scene.h"
#include <vector>

class TitleScene : public Scene {
public:
    TitleScene();
    ~TitleScene() override;
    bool Load() override;
    bool ProccessInput() override;

private:
};