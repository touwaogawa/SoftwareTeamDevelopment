#pragma once
#include "../../../utils/src/math.h"
#include "../component.h"
#include <vector>
class Transform : public Component {
public:
    Transform(class GameObject& owner);
    ~Transform() override;

    Transform* const GetParent() const { return mParent; }
    void SetParent(Transform* parent, bool instantiateInWorldSpace = true);
    const std::vector<Transform* const>& GetChildren() const { return mChildren; }

    // ワールド
    Vector3 GetWorldPosition() const { return mWorldPosition; }
    void SetWorldPosition(Vector3 position);
    Vector3 GetWorldScale() const { return mWorldScale; }
    void SetWorldScale(Vector3 scale);
    Quaternion GetWorldRotation() const { return mWorldRotation; }
    void SetWorldRotation(Quaternion rotation);
    Vector3 GetWorldEulerAngles() const;
    void SetWorldEulerAngles(Vector3 eulerAngles);

    Matrix4 GetWorldMatrix() const;

    // local
    Vector3 GetLocalPosition() const { return mLocalPosition; }
    void SetLocalPosition(Vector3 position);
    Vector3 GetLocalScale() const { return mLocalScale; }
    void SetLocalScale(Vector3 scale);
    Quaternion GetLocalRotation() const { return mLocalRotation; }
    void SetLocalRotation(Quaternion rotation);
    Vector3 GetLocalEulerAngles() const;
    void SetLocalEulerAngles(Vector3 eulerAngles);

    Matrix4 GetLocalMatrix() const;

private:
    // 保留
    void Enable() override { mIsOwnerActive = true; }
    void Disable() override { mIsOwnerActive = false; }
    bool mIsOwnerActive;

    Transform* mParent;
    std::vector<Transform* const> mChildren;

    // ワールド
    Vector3 mWorldPosition;
    Vector3 mWorldScale;
    Quaternion mWorldRotation;

    // ローカル
    Vector3 mLocalPosition;
    Vector3 mLocalScale;
    Quaternion mLocalRotation;

    void RemoveChild(Transform* child);
    void AddChild(Transform* child) { mChildren.push_back(this); }

    void UpdateWorldPosition();
    void UpdateWorldScale();
    void UpdateWorldRotation();
};