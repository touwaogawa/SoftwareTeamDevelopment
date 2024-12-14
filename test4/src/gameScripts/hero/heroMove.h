#pragma once
#include "../../beySmashEngine.h"

class HeroMove : public Behaviour {
public:
    explicit HeroMove(class GameObject* owner)
        : Behaviour(owner)
    {
    }
    ~HeroMove();
    void Start() override
    {
    }
    void Update() override
    {
        if (Input::GetKey(SDL_SCANCODE_W)) {
            Vector3 transform = mOwner->GetTransform()->GetWorldPosition();
            transform.z -= 1.0f;
            mOwner->GetTransform()->SetWorldPosition(transform);
        }
        if (Input::GetKey(SDL_SCANCODE_S)) {
            Vector3 transform = mOwner->GetTransform()->GetWorldPosition();
            transform.z += 1.0f;
            mOwner->GetTransform()->SetWorldPosition(transform);
        }
        if (Input::GetKey(SDL_SCANCODE_A)) {
            Vector3 transform = mOwner->GetTransform()->GetWorldPosition();
            transform.x -= 1.0f;
            mOwner->GetTransform()->SetWorldPosition(transform);
        }
        if (Input::GetKey(SDL_SCANCODE_D)) {
            Vector3 transform = mOwner->GetTransform()->GetWorldPosition();
            transform.x += 1.0f;
            mOwner->GetTransform()->SetWorldPosition(transform);
        }
    }
    void LateUpdate() override
    {
    }

private:
};