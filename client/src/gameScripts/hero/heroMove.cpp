#include "heroMove.h"
#include "../../beySmashEngine.h"
#include "hero.h"

HeroMove::HeroMove(GameObject* owner)
    : Behaviour(owner)
{
}

void HeroMove::Start()
{
    mHero = static_cast<Hero*>(mOwner);
}
namespace {
void show(Transform* transform)
{
    std::cout << "heromove" << std::endl;
    Quaternion wq = transform->GetWorldRotation();
    std::cout << " wqx:" << wq.x << " wqy:" << wq.y << " wqz:" << wq.z << " wqw:" << wq.w << std::endl;
    Quaternion lq = transform->GetLocalRotation();
    std::cout << " lqx:" << lq.x << " lqy:" << lq.y << " lqz:" << lq.z << " lqw:" << lq.w << std::endl;
    Vector3 wpos = transform->GetWorldPosition();
    std::cout << " wposx:" << wpos.x << " wposy:" << wpos.y << " wposz:" << wpos.z << std::endl;
    Vector3 lpos = transform->GetLocalPosition();
    std::cout << " lposx:" << lpos.x << " lposy:" << lpos.y << " lposz:" << lpos.z << std::endl;
    Vector3 wscale = transform->GetWorldScale();
    std::cout << " wscalex:" << wscale.x << " wscaley:" << wscale.y << " wscalez:" << wscale.z << std::endl;
    Vector3 lscale = transform->GetLocalScale();
    std::cout << " lscalex:" << lscale.x << " lscaley:" << lscale.y << " lscalez:" << lscale.z << std::endl;
    if (transform->GetParent() == nullptr)
        std::cout << "noparent" << std::endl;
}

}
void HeroMove::Update()
{
    UpdatePosision();
}
void HeroMove::LateUpdate()
{
}

// ##############################################

void HeroMove::UpdatePosision()
{
    Vector3 pos = mTransform->GetWorldPosition();
    std::cout << "pos_x: " << pos.x << std::endl;
    std::cout << "pos_y: " << pos.y << std::endl;
    Vector2 ma = mHero->currentMoveAxis;
    float cs   = mHero->currentSpeed;
    std::cout << "cs " << cs << std::endl;
    std::cout << "ma_x " << ma.x << std::endl;
    std::cout << "ma_x " << ma.y << std::endl;
    pos.x += cs * ma.x;
    pos.z += cs * ma.y;
    // pos.x += 0.3;
    // pos.z += 0.3;
    mOwner->GetTransform()->SetWorldPosition(pos);
}