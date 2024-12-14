#pragma once

#include "scene.h"

class TestScene : public Scene {
public:
    TestScene();
    void Load() override;
    // 最初のフレーム
    void Start() override;
    // 入力と状態が決まった後
    void Update() override;
    // 物理演算が終わった後
    void LateUpdate() override;

private:
    int mFrameCount;
};