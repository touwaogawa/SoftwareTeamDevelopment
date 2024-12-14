#include "beyMove.h"
#include "../../beySmashEngine.h"

BeyMove::BeyMove(GameObject* owner)
    : Behaviour(owner)
{
}

void BeyMove::Start()
{
}
namespace {

void show(Transform* transform)
{
    Quaternion wq = transform->GetWorldRotation();
    std::cout << " wqx:" << wq.x << " wqy:" << wq.y << " wqz:" << wq.z << " wqw:" << wq.w << std::endl;
    Quaternion lq = transform->GetLocalRotation();
    std::cout << " lqx:" << lq.x << " lqy:" << lq.y << " lqz:" << lq.z << " lqw:" << lq.w << std::endl;
    Vector3 wpos = transform->GetWorldPosition();
    std::cout << " wposx:" << wpos.x << " wposy:" << wpos.y << " wposz:" << wpos.z << std::endl;
    Vector3 lpos = transform->GetLocalPosition();
    std::cout << " lposx:" << lpos.x << " lposy:" << lpos.y << " lposz:" << lpos.z << std::endl;
}
}
void BeyMove::Update()
{
    if (Input::GetKeyDown(SDL_SCANCODE_O)) {
        show(mOwner->GetTransform());
    }
    static float spinPower = 0.1;
    static float spin      = 0.0f;

    if (spinPower > 0.3f)
        spinPower -= 0.01;
    if (spinPower < 0.3f)
        spinPower -= 0.04f;
    if (spinPower < 0.03f)
        spinPower = 0.03f;

    if (Input::GetKey(SDL_SCANCODE_E)) {
        if (spinPower < 2.0f)
            spinPower += 0.03;
    }

    spin += spinPower;
    if (spin > 2 * Math::Pi)
        spin = fmod(spin, 2 * Math::Pi);
    if (Input::GetKey(SDL_SCANCODE_LEFT)) {
        Vector3 pos = mOwner->GetTransform()->GetLocalPosition();
        pos.x -= 0.1f;
        mOwner->GetTransform()->SetLocalPosition(pos);
    }
    if (Input::GetKey(SDL_SCANCODE_RIGHT)) {
        Vector3 pos = mOwner->GetTransform()->GetLocalPosition();
        pos.x += 0.1f;
        mOwner->GetTransform()->SetLocalPosition(pos);
    }
    // if (Input::GetKey(SDL_SCANCODE_A)) {
    //     Vector3 pos = mOwner->GetTransform()->GetWorldPosition();
    //     pos.x -= 1.0f;
    //     mOwner->GetTransform()->SetWorldPosition(pos);
    // }
    // if (Input::GetKey(SDL_SCANCODE_D)) {
    //     Vector3 pos = mOwner->GetTransform()->GetWorldPosition();
    //     pos.x += 1.0f;
    //     mOwner->GetTransform()->SetWorldPosition(pos);
    // }
    // std::cout << mOwner->GetTransform()->GetLocalPosition().x << std::endl;

    mOwner->GetTransform()->SetLocalRotation(Quaternion(0.0f, spin, 0.0f));
    // Matrix4 rot = Matrix4::CreateScale(mOwner->GetTransform()->GetLocalRotation());
    // Matrix4 scale = Matrix4::CreateScale(mOwner->GetTransform()->GetLocalScale());
    // Vector3 lpos = mOwner->GetTransform()->GetLocalPosition();
    // Vector3 lposb(-lpos.x, -lpos.y, -lpos.z);
    // Matrix4 pos  = Matrix4::CreateTranslation(lpos);
    // Matrix4 posb = Matrix4::CreateTranslation(lposb);
    // mOwner->GetTransform()->TransformationLocalMatrix(pos * Matrix4::CreateRotationY(spin) * posb);
}
void BeyMove::LateUpdate()
{
}
