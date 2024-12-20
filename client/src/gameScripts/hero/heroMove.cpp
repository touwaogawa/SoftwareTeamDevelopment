#include "heroMove.h"
#include "../../beySmashEngine.h"

HeroMove::HeroMove(GameObject* owner)
    : Behaviour(owner)
{
}

void HeroMove::Start()
{
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
    // Quaternion q = mOwner->GetTransform()->GetWorldRotation();
    // std::cout << q.x << q.y << q.z << q.w << std::endl;

    // if (Input::GetKeyDown(SDL_SCANCODE_P)) {
    //     show(mOwner->GetTransform());
    // }
    // if (Input::GetKey(SDL_SCANCODE_W)) {
    //     Vector3 pos = mOwner->GetTransform()->GetWorldPosition();
    //     pos.z -= 0.1f;
    //     mOwner->GetTransform()->SetWorldPosition(pos);
    // }
    // if (Input::GetKey(SDL_SCANCODE_S)) {
    //     Vector3 pos = mOwner->GetTransform()->GetWorldPosition();
    //     pos.z += 0.1f;
    //     mOwner->GetTransform()->SetWorldPosition(pos);
    // }
    // if (Input::GetKey(SDL_SCANCODE_A)) {
    //     Vector3 pos = mOwner->GetTransform()->GetWorldPosition();
    //     pos.x -= 0.1f;
    //     mOwner->GetTransform()->SetWorldPosition(pos);
    // }
    // if (Input::GetKey(SDL_SCANCODE_D)) {
    //     Vector3 pos = mOwner->GetTransform()->GetWorldPosition();
    //     pos.x += 0.1f;
    //     mOwner->GetTransform()->SetWorldPosition(pos);
    // }
    // if (Input::GetKey(SDL_SCANCODE_Q)) {
    //     Vector3 pos = mOwner->GetTransform()->GetWorldPosition();
    //     pos.y += 0.1f;
    //     mOwner->GetTransform()->SetWorldPosition(pos);
    // }
    // if (Input::GetKey(SDL_SCANCODE_Z)) {
    //     Vector3 pos = mOwner->GetTransform()->GetWorldPosition();
    //     pos.y -= 0.1f;
    //     mOwner->GetTransform()->SetWorldPosition(pos);
    // }
    // static float spin = 0.0f;
    // if (Input::GetKey(SDL_SCANCODE_J)) {
    //     spin += 0.1f;
    //     mOwner->GetTransform()->SetLocalRotation(Quaternion(0.0f, spin, 0.0f));
    // }
    // if (Input::GetKey(SDL_SCANCODE_K)) {
    //     spin -= 0.1f;
    //     mOwner->GetTransform()->SetLocalRotation(Quaternion(0.0f, spin, 0.0f));
    // }
    // if (Input::GetKey(SDL_SCANCODE_C)) {
    //     Vector3 scale = mOwner->GetTransform()->GetWorldScale();
    //     scale.x += 0.1f;
    //     scale.y += 0.1f;
    //     scale.z += 0.1f;
    //     mOwner->GetTransform()->SetWorldScale(scale);
    // }
    // if (Input::GetKey(SDL_SCANCODE_V)) {
    //     Vector3 scale = mOwner->GetTransform()->GetWorldScale();
    //     scale.x -= 0.1f;
    //     scale.y -= 0.1f;
    //     scale.z -= 0.1f;
    //     mOwner->GetTransform()->SetWorldScale(scale);
    // }
}
void HeroMove::LateUpdate()
{
}
