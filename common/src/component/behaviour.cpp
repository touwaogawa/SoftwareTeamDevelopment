#include "behaviour.h"
#include "../gameObject.h"

Behaviour::Behaviour(GameObject* owner)
    : Component(owner)
    , mState(BehaviourState::PreStart)
    , mEnabled(true)
{
}
void Behaviour::SetEnabled(bool enabled)
{
    if (mEnabled != enabled) {
        mEnabled = enabled;
        if (mOwner->GetIsActive()) {
            if (mEnabled) {
                OnEnable();
            } else {
                OnDisable();
            }
        }
    }
}

bool Behaviour::GetIsActiveAndEnabled() const
{
    return mEnabled && mOwner->GetIsActive();
}

void Behaviour::Enable()
{
    if (mEnabled) {
        OnEnable();
    }
}
void Behaviour::Disable()
{
    if (mEnabled) {
        OnDisable();
    }
}