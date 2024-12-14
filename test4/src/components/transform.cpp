#include "transform.h"
#include "../component.h"
#include "../gameObject.h"
#include "../math.h"
#include <algorithm>
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
}
Vector3 Transform::GetWorldPosition()
{
    return mWorldPosition;
}
void Transform::SetWorldPosition(Vector3 position)
{
    mWorldPosition = position;
    AdoptfromWorldValue();
}
void Transform::SetWorldPosition(float x, float y, float z)
{
    mWorldPosition.x = x;
    mWorldPosition.y = y;
    mWorldPosition.z = z;
    AdoptfromWorldValue();
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
}
void Transform::SetWorldScale(Vector3 scale)
{
    mWorldScale = scale;
    AdoptfromWorldValue();
}
void Transform::SetWorldScale(float scale)
{
    mWorldScale.x = scale;
    mWorldScale.y = scale;
    mWorldScale.z = scale;
    AdoptfromWorldValue();
}
Quaternion Transform::GetWorldRotation()
{
    return mWorldRotation;
}
void Transform::SetWorldRotation(Quaternion rotation)
{
    mWorldRotation = rotation;
    AdoptfromWorldValue();
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
}
Vector3 Transform::GetLocalPosition()
{
    return mLocalPosition;
}
void Transform::SetLocalPosition(Vector3 position)
{
    mLocalPosition = position;
    AdoptfromLocalValue();
}
void Transform::SetLocalPosition(float x, float y, float z)
{
    mLocalPosition.x = x;
    mLocalPosition.y = y;
    mLocalPosition.z = z;
    AdoptfromLocalValue();
}
Vector3 Transform::GetLocalScale()
{
    return mLocalScale;
}
void Transform::SetLocalScale(float x, float y, float z)
{
    mWorldScale.x = x;
    mWorldScale.y = y;
    mWorldScale.z = z;
    AdoptfromLocalValue();
}
void Transform::SetLocalScale(Vector3 scale)
{
    mWorldScale = scale;
    AdoptfromLocalValue();
}
void Transform::SetLocalScale(float scale)
{
    mWorldScale.x = scale;
    mWorldScale.y = scale;
    mWorldScale.z = scale;
    AdoptfromLocalValue();
}
Quaternion Transform::GetLocalRotation()
{
    return mLocalRotation;
}
void Transform::SetLocalRotation(Quaternion rotation)
{
    mLocalRotation = rotation;
    AdoptfromLocalValue();
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
        mLocalMatrix = Matrix4::Invert(mParent->mWorldMatrix) * mWorldMatrix;
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

    for (Transform* child : mChildren) {
        child->AdoptParentTransform();
    }
}
void Transform::AdoptfromLocalMatrix()
{

    if (mParent == nullptr) {
        mWorldMatrix = mLocalMatrix;
    } else {
        mWorldMatrix = mParent->mWorldMatrix * mLocalMatrix;
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

    for (Transform* child : mChildren) {
        child->AdoptParentTransform();
    }
}
void Transform::AdoptfromWorldValue()
{
    mWorldMatrix = Matrix4::CreateScale(mWorldScale) * Matrix4::CreateFromQuaternion(mWorldRotation) * Matrix4::CreateTranslation(mWorldPosition);

    if (mParent == nullptr) {
        mLocalMatrix = mWorldMatrix;
    } else {
        mLocalMatrix = Matrix4::Invert(mParent->mWorldMatrix) * mWorldMatrix;
    }

    ConvertMatrixToValues(mLocalMatrix,
        mLocalPosition,
        mLocalRotation,
        mLocalScale,
        mLocalEulerAngles);

    for (Transform* child : mChildren) {
        child->AdoptParentTransform();
    }
}
void Transform::AdoptfromLocalValue()
{
    mLocalMatrix = Matrix4::CreateScale(mLocalScale) * Matrix4::CreateFromQuaternion(mLocalRotation) * Matrix4::CreateTranslation(mLocalPosition);

    if (mParent == nullptr) {
        mWorldMatrix = mLocalMatrix;
    } else {
        mWorldMatrix = mParent->mWorldMatrix * mLocalMatrix;
    }

    ConvertMatrixToValues(mWorldMatrix,
        mWorldPosition,
        mWorldRotation,
        mWorldScale,
        mWorldEulerAngles);

    for (Transform* child : mChildren) {
        child->AdoptParentTransform();
    }
}

void Transform::AdoptParentTransform()
{
    if (mParent == nullptr) {
        mWorldMatrix = mLocalMatrix;
    } else {
        mWorldMatrix = mParent->mWorldMatrix * mLocalMatrix;
    }
    ConvertMatrixToValues(mWorldMatrix,
        mWorldPosition,
        mWorldRotation,
        mWorldScale,
        mWorldEulerAngles);

    for (Transform* child : mChildren) {
        child->AdoptParentTransform();
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
    eulerAngleOut = matrix.GetEulerAngles();
    rotOut        = Quaternion::GetRotation(matrix);
    scaleOut      = matrix.GetScale();
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