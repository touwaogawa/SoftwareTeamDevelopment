#include "transform.h"
#include <algorithm>
#include <iostream>

Transform::Transform(GameObject* owner)
    : Component(owner)
    , mParent(nullptr)
    , mWorldPosition(Vector3(0.0f, 0.0f, 0.0f))
    , mWorldScale(Vector3(1.0f, 1.0f, 1.0f))
    , mWorldRotation(Quaternion(0.0f, 0.0f, 0.0f, 1.0f))
    , mLocalPosition(Vector3(0.0f, 0.0f, 0.0f))
    , mLocalScale(Vector3(1.0f, 1.0f, 1.0f))
    , mLocalRotation(Quaternion(0.0f, 0.0f, 0.0f, 1.0f))
{
}

Transform::~Transform()
{
    if (mParent) {
        mParent->RemoveChild(this);
    }
}

void Transform::SetParent(Transform* parent, bool instantiateInWorldSpace)
{
    if (parent == this) {
        std::cout << "parent loop error" << std::endl;
        return;
    }
    if (mParent) {
        mParent->RemoveChild(this);
    }
    mParent = parent;

    if (instantiateInWorldSpace) {
        SetWorldPosition(mWorldPosition);
        SetWorldScale(mWorldScale);
        SetWorldRotation(mWorldRotation);
    } else {
        UpdateWorldPosition();
        UpdateWorldScale();
        UpdateWorldRotation();
    }

    if (mParent) {
        mParent->AddChild(this);
    }
}

// world
void Transform::SetWorldPosition(Vector3 position)
{
    mWorldPosition = position;

    if (mParent) {
        mLocalPosition = mWorldPosition - mParent->mWorldPosition;
    } else {
        mLocalPosition = mWorldPosition;
    }
    for (auto* const& child : mChildren) {
        child->UpdateWorldPosition();
    }
}
void Transform::SetWorldScale(Vector3 scale)
{
    mWorldScale = scale;
    if (mParent) {
        mLocalScale.x = mWorldScale.x / mParent->mWorldScale.x;
        mLocalScale.y = mWorldScale.y / mParent->mWorldScale.y;
        mLocalScale.z = mWorldScale.z / mParent->mWorldScale.z;
    } else {
        mLocalScale = mWorldScale;
    }
    for (auto* const& child : mChildren) {
        child->UpdateWorldScale();
    }
}
void Transform::SetWorldRotation(Quaternion rotation)
{
    mWorldRotation = rotation;
    if (mParent) {
        Quaternion inverseQ = mParent->mWorldRotation;
        inverseQ.Normalize();
        inverseQ.Conjugate();
        // mLocalRotation = Quaternion::Concatenate(inverseQ, mWorldRotation);
        mLocalRotation = Quaternion::Concatenate(mWorldRotation, inverseQ);

    } else {
        mLocalRotation = mWorldRotation;
    }
    for (auto* const& child : mChildren) {
        child->UpdateWorldRotation();
    }
}

void Transform::SetWorldEulerAngles(Vector3 eulerAngles)
{
    float halfPitch = eulerAngles.x * 0.5f;
    float halfYaw   = eulerAngles.y * 0.5f;
    float halfRoll  = eulerAngles.z * 0.5f;

    // 各軸に対するサインとコサインを計算
    float sinPitch = Math::Sin(halfPitch);
    float cosPitch = Math::Cos(halfPitch);
    float sinYaw   = Math::Sin(halfYaw);
    float cosYaw   = Math::Cos(halfYaw);
    float sinRoll  = Math::Sin(halfRoll);
    float cosRoll  = Math::Cos(halfRoll);

    // クォータニオンの成分を計算
    float w = cosRoll * cosPitch * cosYaw + sinRoll * sinPitch * sinYaw;
    float x = sinRoll * cosPitch * cosYaw - cosRoll * sinPitch * sinYaw;
    float y = cosRoll * sinPitch * cosYaw + sinRoll * cosPitch * sinYaw;
    float z = cosRoll * cosPitch * sinYaw - sinRoll * sinPitch * cosYaw;

    SetWorldRotation(Quaternion(x, y, z, w));
}

Matrix4 Transform::GetWorldMatrix() const
{
    Matrix4 translation(Matrix4::CreateTranslation(mWorldPosition));
    Matrix4 rotation(Matrix4::CreateFromQuaternion(mWorldRotation));
    Matrix4 scale(Matrix4::CreateScale(mWorldScale));

    return scale * rotation * translation;
}

// local
void Transform::SetLocalPosition(Vector3 position)
{
    mLocalPosition = position;

    if (mParent) {
        mWorldPosition = mLocalPosition + mParent->mLocalPosition;
    } else {
        mWorldPosition = mLocalPosition;
    }
    for (auto* const& child : mChildren) {
        child->UpdateWorldPosition();
    }
}
void Transform::SetLocalScale(Vector3 scale)
{
    mLocalScale = scale;

    if (mParent) {
        mWorldScale = mLocalScale * mParent->mLocalScale;
    } else {
        mWorldScale = mLocalScale;
    }
    for (auto* const& child : mChildren) {
        child->UpdateWorldScale();
    }
}
void Transform::SetLocalRotation(Quaternion rotation)
{
    mLocalRotation = rotation;

    if (mParent) {
        // mWorldRotation = Quaternion::Concatenate(mParent->mWorldRotation, mLocalRotation);
        mWorldRotation = Quaternion::Concatenate(mLocalRotation, mParent->mWorldRotation);

    } else {
        mWorldRotation = mLocalRotation;
    }
    for (auto* const& child : mChildren) {
        child->UpdateWorldRotation();
    }
}
void Transform::SetLocalEulerAngles(Vector3 eulerAngles)
{
    float halfPitch = eulerAngles.x * 0.5f;
    float halfYaw   = eulerAngles.y * 0.5f;
    float halfRoll  = eulerAngles.z * 0.5f;

    // 各軸に対するサインとコサインを計算
    float sinPitch = Math::Sin(halfPitch);
    float cosPitch = Math::Cos(halfPitch);
    float sinYaw   = Math::Sin(halfYaw);
    float cosYaw   = Math::Cos(halfYaw);
    float sinRoll  = Math::Sin(halfRoll);
    float cosRoll  = Math::Cos(halfRoll);

    // クォータニオンの成分を計算
    float w = cosRoll * cosPitch * cosYaw + sinRoll * sinPitch * sinYaw;
    float x = sinRoll * cosPitch * cosYaw - cosRoll * sinPitch * sinYaw;
    float y = cosRoll * sinPitch * cosYaw + sinRoll * cosPitch * sinYaw;
    float z = cosRoll * cosPitch * sinYaw - sinRoll * sinPitch * cosYaw;

    SetLocalRotation(Quaternion(x, y, z, w));
}

Matrix4 Transform::GetLocalMatrix() const
{
    Matrix4 translation(Matrix4::CreateTranslation(mLocalPosition));
    Matrix4 rotation(Matrix4::CreateFromQuaternion(mLocalRotation));
    Matrix4 scale(Matrix4::CreateScale(mLocalScale));

    // return scale * rotation * translation;
    return translation * rotation * scale;
}

// private ###################################
void Transform::RemoveChild(Transform* child)
{
    auto end = std::remove(mChildren.begin(), mChildren.end(), child);
    mChildren.erase(end, mChildren.end());
}

void Transform::UpdateWorldPosition()
{
    mWorldPosition = mParent->mWorldPosition + mLocalPosition;
    for (auto& child : mChildren) {
        child->UpdateWorldPosition();
    }
}
void Transform::UpdateWorldScale()
{
    mWorldScale = mParent->mWorldScale * mLocalScale;
    for (auto& child : mChildren) {
        child->UpdateWorldScale();
    }
}
void Transform::UpdateWorldRotation()
{
    // mWorldRotation = Quaternion::Concatenate(mParent->mWorldRotation, mLocalRotation);
    mWorldRotation = Quaternion::Concatenate(mLocalRotation, mParent->mWorldRotation);
    for (auto& child : mChildren) {
        child->UpdateWorldRotation();
    }
}