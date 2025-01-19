#include "scalingMove.h"
#include "../../../../../../common/src/component/transform.h"
#include "../../../../../../utils/src/math.h"
#include "../../../gameObject/hero.h"
#include <iostream>

ScalingMove::ScalingMove(GameObject* owner, Vector3 scaleVelocity, int lifeFrame)
    : Behaviour(owner)
    , mScaleVelocity(scaleVelocity)
    , mLifeFrame(lifeFrame)
    , mFrame(0)
{
    // std::cout << "ScalingMove constructor" << std::endl;
}
void ScalingMove::Update()
{
    if (mFrame < mLifeFrame) {
        GetTransform()->SetLocalScale(GetTransform()->GetLocalScale() * mScaleVelocity);
        mFrame++;
    } else if (mFrame == mLifeFrame) {
        mOwner->Destroy();
        mFrame++;
    }
}