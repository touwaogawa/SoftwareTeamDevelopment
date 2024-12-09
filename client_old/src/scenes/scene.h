#pragma once

// インターフェース
class Scene {
public:
    Scene();
    // ロード
    virtual void Load();
    // 最初のフレーム
    virtual void Start();
    // 入力と状態が決まった後
    virtual void Update();
    // 物理演算が終わった後
    virtual void LateUpdate();
};