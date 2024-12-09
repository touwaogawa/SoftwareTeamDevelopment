#pragma once

// インターフェース
class Scene {
public:
    virtual void Awake();
    virtual void Start();
    // 入力と状態が決まった後
    virtual void Update();
    // 物理演算が終わった後
    virtual void LateUpdate();
};