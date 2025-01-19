#include "faceDirMove.h"
#include "../../../../../../common/src/component/transform.h"
#include "../../../../../../utils/src/math.h"
#include "../../../gameObject/hero.h"
#include <iostream>

FaceDirMove::FaceDirMove(GameObject* owner, Hero* hero)
    : Behaviour(owner)
    , mHero(hero)
{
    // std::cout << "FaceDirMove constructor" << std::endl;
}

void FaceDirMove::Start()
{
    GetTransform()->SetLocalPosition(Vector3(0.0f, 0.1f, -2.0f));
}
void FaceDirMove::Update()
{

    if (mHero->mCurrentStatus.state != HeroState::Death) {
        if (mHero->mCurrentStatus.stopFrame <= 0) {
            Vector2 faceDir = mHero->mCurrentStatus.faceDir;
            if (faceDir.Length() > 0.0f) {
                float angle  = Math::Atan2(faceDir.x, -faceDir.y);
                Quaternion q = Quaternion(Vector3(0.0f, 1.0f, 0.0f), -angle);
                Vector3 pos  = Vector3::Transform(Vector3(0.0f, 0.1f, -2.0f), q);
                GetTransform()->SetWorldRotation(q);
                GetTransform()->SetLocalPosition(pos);
            }
        }
    }
}