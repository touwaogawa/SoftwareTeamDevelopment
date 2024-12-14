#pragma once

#include "scene.h"

class BattleScene : public Scene {
public:
    void Load() override;
    void Start() override;
    // 入力と状態が決まった後
    void Update() override;
    // 物理演算が終わった後
    void LateUpdate() override;

private:
    // player(人、独楽、当たり判定)
    // 床
    // 場外判定
};