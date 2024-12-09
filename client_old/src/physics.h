#pragma once

#include <vector>
class Physics {
public:
    // 動的コライダー同士の当たり判定
    static void DynamicIntersect();

private:
    static std::vector<class Collider*> mDynamicColliders;
    static std::vector<class Collider*> mStaticColliders;
};