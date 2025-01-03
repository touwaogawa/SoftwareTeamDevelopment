#include "beyMove.h"
#include "../../beySmashEngine.h"
#include "bey.h"
BeyMove::BeyMove(GameObject* owner)
    : Behaviour(owner)
    , mSpinPower(0.0f)
{
    std::cout << "beyMove constructer" << std::endl;
}

void BeyMove::Start()
{
    std::cout << "beyMove start" << std::endl;
    mSpinPower    = 0.1;
    mMinSpinPower = 0.1;
}
namespace {

void show(Transform* transform)
{
    std::cout << "beymove" << std::endl;
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
    // if (Input::GetKeyDown(SDL_SCANCODE_O)) {
    //     show(mOwner->GetTransform());
    // }

    // if (Input::GetKey(SDL_SCANCODE_E)) {
    //     if (mSpinPower < 1.3f)
    //         mSpinPower += 0.005f;
    // } else {
    //     if (mSpinPower > mMinSpinPower) {
    //         mSpinPower -= 0.001f;
    //     } else if (mSpinPower < mMinSpinPower) {
    //         mSpinPower = mMinSpinPower;
    //     }
    // }

    // if (Input::GetKey(SDL_SCANCODE_LEFT)) {
    //     Vector3 pos = mOwner->GetTransform()->GetLocalPosition();
    //     pos.x -= 0.1f;
    //     mOwner->GetTransform()->SetLocalPosition(pos);
    // }
    // if (Input::GetKey(SDL_SCANCODE_RIGHT)) {
    //     Vector3 pos = mOwner->GetTransform()->GetLocalPosition();
    //     pos.x += 0.1f;
    //     mOwner->GetTransform()->SetLocalPosition(pos);
    // }
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
    // mOwner->GetTransform()->TransformationLocalMatrix(Matrix4::CreateRotationY(mSpinPower));

    // if (Input::GetButton("A")) {
    //     std::cout << "joycona" << std::endl;
    // }
    // mOwner->GetTransform()->SetLocalRotation(Quaternion(0.0f, -spin, 0.0f));
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
