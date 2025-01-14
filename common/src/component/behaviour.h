#pragma once
#include "../component.h"
#include <reactphysics3d/reactphysics3d.h>

enum class BehaviourState {
    PreStart,
    Started,
    BehaviourStateNum
};

class Behaviour : public Component {
public:
    /// @brief Contructor
    /// @param owner
    explicit Behaviour(class GameObject* owner);

    /// @brief DEstructor
    virtual ~Behaviour() = default;

    BehaviourState GetState() const { return mState; }
    void SetState(BehaviourState behaviourState) { mState = behaviourState; }
    bool GetEnabled() const { return mEnabled; }
    void SetEnabled(bool enabled);
    bool GetIsActiveAndEnabled() const;

    /// @brief オブジェクトが初めて生成されるときに1回だけ呼ばれる
    virtual void Awake() { }

    virtual void Start() { }
    virtual void Update() { }
    virtual void LateUpdate() { }

    virtual void OnCollisionEnter(const rp3d::Collider* self, const rp3d::Collider* opponent, const rp3d::CollisionCallback::ContactPair& pair) { }
    virtual void OnCollisionStay(const rp3d::Collider* self, const rp3d::Collider* opponent, const rp3d::CollisionCallback::ContactPair& pair) { }
    virtual void OnCollisionExit(const rp3d::Collider* self, const rp3d::Collider* opponent, const rp3d::CollisionCallback::ContactPair& pair) { }

    virtual void OnOverlapEnter(const rp3d::Collider* self, const rp3d::Collider* opponent, const rp3d::OverlapCallback::OverlapPair& pair) { }
    virtual void OnOverlapStay(const rp3d::Collider* self, const rp3d::Collider* opponent, const rp3d::OverlapCallback::OverlapPair& pair) { }
    virtual void OnOverlapExit(const rp3d::Collider* self, const rp3d::Collider* opponent, const rp3d::OverlapCallback::OverlapPair& pair) { }

    virtual void OnEnable() { }
    virtual void OnDisable() { }

private:
    void Enable() override;
    void Disable() override;

    BehaviourState mState;
    bool mEnabled;
};