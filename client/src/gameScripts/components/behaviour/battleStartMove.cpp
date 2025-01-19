#include "battleStartMove.h"
#include "../../../../../common/src/component/transform.h"
#include "../../../../../common/src/gameObject.h"
#include "../../../../../utils/src/math.h"
// #include "../../../renderer.h"

BattleStartMove::BattleStartMove(GameObject* owner)
    : Behaviour(owner)
    , x(1920.0f / 2.0f)
    , md(true)

{
}

void BattleStartMove::Start()
{
    GetTransform()->SetWorldPosition(Vector3(x, 0.0f, 0.0f));
}

void BattleStartMove::Update()
{
    float x = GetTransform()->GetWorldPosition().x;
    float w = 100;
    if (960 - w < x && x < 960 + w) {
        x -= w * 2 / 20;
    } else {
        x -= 300.0f;
    }
    GetTransform()->SetWorldPosition(Vector3(x, 0.0f, 0.0f));
    if (x < -1920.0f / 2.0f) {
        if (md) {
            mOwner->Destroy();
            md = false;
        }
    }
}