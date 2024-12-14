#include "physics.h"
#include "collision.h"
#include "components/collider.h"

std::vector<class Collider*> Physics::mDynamicColliders;
std::vector<class Collider*> Physics::mStaticColliders;

void Physics::DynamicIntersect()
{
    for (Collider* collider : mDynamicColliders) {
        for (size_t i = 0; i < mDynamicColliders.size(); i++) {
            // 形ごとに異なる処理を行いたい(未)
            Collision::Intersect();
        }
    }
}