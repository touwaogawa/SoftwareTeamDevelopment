#include "transform.h"
#include "../../../utils/src/math.h"
#include "../component.h"
#include <algorithm>
#include <iostream>
Transform::Transform(GameObject* owner, Transform* parent)
    : Component(owner)
    , mParent(nullptr)
{
    SetParent(parent);
}

Transform::~Transform()
{
    if (mParent != nullptr) {
        mParent->RemoveChild(this);
    }
}

Transform* Transform::GetParent() const
{
    return mParent;
}

void Transform::SetParent(Transform* newParent)
{
    if (mParent != nullptr) {
        mParent->RemoveChild(this);
    }
    mParent = newParent;
    if (mParent != nullptr) {
        mParent->AddChild(this);
    }
    AdoptfromLocalMatrix();
}

std::vector<Transform*> Transform::GetChildren()
{
    return mChildren;
}

// ワールド
Matrix4 Transform::GetWorldMatrix()
{
    return mWorldMatrix;
}
void Transform::SetWorldMatrix(Matrix4 matrix)
{
    mWorldMatrix = matrix;
    AdoptfromWorldMatrix();
    AdoptParentTransformForAllChildren();
}
Vector3 Transform::GetWorldPosition()
{
    return mWorldPosition;
}
void Transform::SetWorldPosition(Vector3 position)
{
    mWorldPosition = position;
    AdoptfromWorldValue();
    AdoptParentTransformForAllChildren();
}
void Transform::SetWorldPosition(float x, float y, float z)
{
    mWorldPosition.x = x;
    mWorldPosition.y = y;
    mWorldPosition.z = z;
    AdoptfromWorldValue();
    AdoptParentTransformForAllChildren();
}
Vector3 Transform::GetWorldScale()
{
    return mWorldScale;
}
void Transform::SetWorldScale(float x, float y, float z)
{
    mWorldScale.x = x;
    mWorldScale.y = y;
    mWorldScale.z = z;
    AdoptfromWorldValue();
    AdoptParentTransformForAllChildren();
}
void Transform::SetWorldScale(Vector3 scale)
{
    mWorldScale = scale;
    AdoptfromWorldValue();
    AdoptParentTransformForAllChildren();
}
void Transform::SetWorldScale(float scale)
{
    mWorldScale.x = scale;
    mWorldScale.y = scale;
    mWorldScale.z = scale;
    AdoptfromWorldValue();
    AdoptParentTransformForAllChildren();
}
Quaternion Transform::GetWorldRotation()
{
    return mWorldRotation;
}
void Transform::SetWorldRotation(Quaternion rotation)
{
    mWorldRotation = rotation;
    AdoptfromWorldValue();
    AdoptParentTransformForAllChildren();
}

Vector3 Transform::GetWorldEulerAngles()
{
    return mWorldEulerAngles;
}
void Transform::SetWorldEulerAngles(Vector3 eulerAngles)
{
    mWorldEulerAngles = eulerAngles;
    mWorldRotation    = Quaternion(mWorldEulerAngles);
    AdoptfromWorldValue();
    AdoptParentTransformForAllChildren();
}

void Transform::TransformationWorldMatrix(Matrix4 translationMat)
{
    mWorldMatrix *= translationMat;
    AdoptfromWorldMatrix();
}

// ローカル
Matrix4 Transform::GetLocalMatrix()
{
    return mLocalMatrix;
}
void Transform::SetLocalMatrix(Matrix4 matrix)
{
    mLocalMatrix = matrix;
    AdoptfromLocalMatrix();
    AdoptParentTransformForAllChildren();
}
Vector3 Transform::GetLocalPosition()
{
    return mLocalPosition;
}
void Transform::SetLocalPosition(Vector3 position)
{
    mLocalPosition = position;
    AdoptfromLocalValue();
    AdoptParentTransformForAllChildren();
}
void Transform::SetLocalPosition(float x, float y, float z)
{
    mLocalPosition.x = x;
    mLocalPosition.y = y;
    mLocalPosition.z = z;
    AdoptfromLocalValue();
    AdoptParentTransformForAllChildren();
}
Vector3 Transform::GetLocalScale()
{
    return mLocalScale;
}
void Transform::SetLocalScale(float x, float y, float z)
{
    mLocalScale.x = x;
    mLocalScale.y = y;
    mLocalScale.z = z;
    AdoptfromLocalValue();
    AdoptParentTransformForAllChildren();
}
void Transform::SetLocalScale(Vector3 scale)
{
    mLocalScale = scale;
    AdoptfromLocalValue();
    AdoptParentTransformForAllChildren();
}
void Transform::SetLocalScale(float scale)
{
    mLocalScale.x = scale;
    mLocalScale.y = scale;
    mLocalScale.z = scale;
    AdoptfromLocalValue();
    AdoptParentTransformForAllChildren();
}
Quaternion Transform::GetLocalRotation()
{
    return mLocalRotation;
}
void Transform::SetLocalRotation(Quaternion rotation)
{
    mLocalRotation = rotation;
    AdoptfromLocalValue();
    AdoptParentTransformForAllChildren();
}

Vector3 Transform::GetLocalEulerAngles()
{
    return mLocalEulerAngles;
}
void Transform::SetLocalEulerAngles(Vector3 eulerAngles)
{
    mLocalEulerAngles = eulerAngles;
    mLocalRotation    = Quaternion(mLocalEulerAngles);
    AdoptfromLocalValue();
    AdoptParentTransformForAllChildren();
}

void Transform::TransformationLocalMatrix(Matrix4 translationMat)
{
    mLocalMatrix *= translationMat;
    AdoptfromLocalMatrix();
}

// ユーティリティ

void Transform::AdoptfromWorldMatrix()
{
    if (mParent == nullptr) {
        mLocalMatrix = mWorldMatrix;
    } else {
        mLocalMatrix = mWorldMatrix * Matrix4::Invert(mParent->mWorldMatrix);
    }

    ConvertMatrixToValues(mWorldMatrix,
        mWorldPosition,
        mWorldRotation,
        mWorldScale,
        mWorldEulerAngles);
    ConvertMatrixToValues(mLocalMatrix,
        mLocalPosition,
        mLocalRotation,
        mLocalScale,
        mLocalEulerAngles);
}
void Transform::AdoptfromLocalMatrix()
{

    if (mParent == nullptr) {
        mWorldMatrix = mLocalMatrix;
    } else {
        mWorldMatrix = mLocalMatrix * mParent->mWorldMatrix;
    }

    ConvertMatrixToValues(mWorldMatrix,
        mWorldPosition,
        mWorldRotation,
        mWorldScale,
        mWorldEulerAngles);
    ConvertMatrixToValues(mLocalMatrix,
        mLocalPosition,
        mLocalRotation,
        mLocalScale,
        mLocalEulerAngles);
}
void Transform::AdoptfromWorldValue()
{
    mWorldMatrix = Matrix4::CreateScale(mWorldScale);
    mWorldMatrix *= Matrix4::CreateFromQuaternion(mWorldRotation);
    mWorldMatrix *= Matrix4::CreateTranslation(mWorldPosition);

    if (mParent == nullptr) {
        mLocalMatrix = mWorldMatrix;
    } else {
        mLocalMatrix = mWorldMatrix * Matrix4::Invert(mParent->mWorldMatrix);
    }

    ConvertMatrixToValues(mLocalMatrix,
        mLocalPosition,
        mLocalRotation,
        mLocalScale,
        mLocalEulerAngles);
}
void Transform::AdoptfromLocalValue()
{
    mLocalMatrix = Matrix4::CreateScale(mLocalScale);
    mLocalMatrix *= Matrix4::CreateFromQuaternion(mLocalRotation);
    mLocalMatrix *= Matrix4::CreateTranslation(mLocalPosition);

    if (mParent == nullptr) {
        mWorldMatrix = mLocalMatrix;
    } else {
        mWorldMatrix = mLocalMatrix * mParent->mWorldMatrix;
    }
    ConvertMatrixToValues(mWorldMatrix,
        mWorldPosition,
        mWorldRotation,
        mWorldScale,
        mWorldEulerAngles);
}

void Transform::AdoptParentTransform()
{
    if (mParent == nullptr) {
        mWorldMatrix = mLocalMatrix;
    } else {
        mWorldMatrix = mLocalMatrix * mParent->mWorldMatrix;
    }
    ConvertMatrixToValues(mWorldMatrix,
        mWorldPosition,
        mWorldRotation,
        mWorldScale,
        mWorldEulerAngles);
}

void Transform::AdoptParentTransformForAllChildren()
{
    for (Transform* child : mChildren) {
        child->AdoptParentTransform();
        child->AdoptParentTransformForAllChildren();
    }
}

void Transform::ConvertMatrixToValues(
    const Matrix4& matrix,
    Vector3& posOut,
    Quaternion& rotOut,
    Vector3& scaleOut,
    Vector3& eulerAngleOut)
{
    posOut        = matrix.GetTranslation();
    scaleOut      = matrix.GetScale();
    eulerAngleOut = matrix.GetEulerAngles();
    rotOut        = matrix.GetRotation();
}

void Transform::AddChild(Transform* child)
{
    mChildren.push_back(child);
}

void Transform::RemoveChild(Transform* child)
{
    auto end = std::remove(mChildren.begin(), mChildren.end(), child);
    mChildren.erase(end, mChildren.end());
}