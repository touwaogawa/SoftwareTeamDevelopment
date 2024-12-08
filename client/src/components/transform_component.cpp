#include "transform_component.h"
#include "../../common/src/common_math.h"

namespace {
Matrix4 ValuesToMatrix(Vector3 scale, Quaternion rotation, Vector3 position);
Vector3 MatrixToPosition(Matrix4 mat);
Vector3 MatrixToScale(Matrix4 mat);
Quaternion MatrixToRotation(Matrix4 mat, Vector3 scale);
}

Transform::Transform(GameObject* owner, Transform* parent)
    : Component(owner)
    , mParent(parent) // 親を設定
{
    if (mParent != nullptr) {
        // 親に自分を子として設定してもらう
        mParent->mChildren.push_back(this);
    }
}
Transform::~Transform()
{
    mParent->RemoveChild(this);
}

// getter setter local
const Vector3& Transform::GetLocalPosition() const
{
    return mLocalPosition;
}
void Transform::SetLocalPosition(Vector3 position)
{
    mLocalPosition = position;
    AdoptTransformFromLocalValue();
    for (Transform* child : mChildren) {
        child->AdoptTransformFromLocalValue();
    }
}
Quaternion Transform::GetLocaRotation() const
{
    return mLocalRotation;
}
void Transform::SetLocalRotation(Quaternion rotation)
{
    mLocalRotation = rotation;
    AdoptTransformFromLocalValue();
    for (Transform* child : mChildren) {
        child->AdoptTransformFromLocalValue();
    }
}
const Vector3& Transform::GetLocalScale() const
{
    return mLocalScale;
}
void Transform::SetLocalScale(Vector3 scale)
{
    mLocalScale = scale;
    AdoptTransformFromLocalValue();
    for (Transform* child : mChildren) {
        child->AdoptTransformFromLocalValue();
    }
}
const Matrix4& Transform::GetLocalMatrix() const
{
    return mLocalMatrix;
}
void Transform::SetLocalMatrix(Matrix4 matrix)
{
    mLocalMatrix = matrix;
    AdoptTransformFromLocalMatrix();
    for (Transform* child : mChildren) {
        child->AdoptTransformFromLocalValue();
    }
}

// getter setter world
const Vector3& Transform::GetWorldPosition() const
{
    return mWorldPosition;
}
void Transform::SetWorldPosition(Vector3 position)
{
    mWorldPosition = position;
    AdoptTransformFromWorldValue();
    for (Transform* child : mChildren) {
        child->AdoptTransformFromLocalValue();
    }
}
Quaternion Transform::GetLocaRotation() const
{
    return mWorldRotation;
}
void Transform::SetWorldRotation(Quaternion rotation)
{
    mWorldRotation = rotation;
    AdoptTransformFromWorldValue();
    for (Transform* child : mChildren) {
        child->AdoptTransformFromLocalValue();
    }
}
const Vector3& Transform::GetWorldScale() const
{
    return mWorldScale;
}
void Transform::SetWorldScale(Vector3 scale)
{
    mWorldScale = scale;
    AdoptTransformFromWorldValue();
    for (Transform* child : mChildren) {
        child->AdoptTransformFromLocalValue();
    }
}
const Matrix4& Transform::GetWorldMatrix() const
{
    return mWorldMatrix;
}
void Transform::SetWorldMatrix(Matrix4 matrix)
{
    mWorldMatrix = matrix;
    AdoptTransformFromWorldMatrix();
    for (Transform* child : mChildren) {
        child->AdoptTransformFromLocalValue();
    }
}
void Transform::MoveParent(Transform* parent)
{
    if (mParent != nullptr) {
        mParent->RemoveChild(this);
    }
    mParent = parent;
    mParent->AddChild(this);
    AdoptTransformFromWorldValue(); // localの値を新しい親を基準に再設定
}

// 親子関係public
Transform* Transform::GetParent() const
{
    return mParent;
}
void MoveParent(Transform* parent)
{
}

std::vector<Transform*> Transform::GetChildren() const
{
    return mChildren;
}

// 親子関係private
void Transform::AddChild(Transform* child)
{
    mChildren.push_back(child);
}

//
void Transform::AdoptTransformFromLocalValue()
{
    // local values > local matrix
    mLocalMatrix = ValuesToMatrix(mLocalScale, mLocalRotation, mLocalPosition);

    // local matrix > world matrix
    mWorldMatrix = mParent->mWorldMatrix * mLocalMatrix;

    // world matrix > world values
    mWorldPosition = MatrixToPosition(mWorldMatrix);
    mWorldScale    = MatrixToScale(mWorldMatrix);
    mWorldRotation = MatrixToRotation(mWorldMatrix, mWorldScale);
}

void Transform::AdoptTransformFromLocalMatrix()
{
    // local matrix > local values
    mLocalPosition = MatrixToPosition(mLocalMatrix);
    mLocalScale    = MatrixToScale(mLocalMatrix);
    mLocalRotation = MatrixToRotation(mLocalMatrix, mLocalScale);

    // local matrix > world matrix
    mWorldMatrix = mParent->mWorldMatrix * mLocalMatrix;

    // world matrix > world values
    mWorldPosition = MatrixToPosition(mWorldMatrix);
    mWorldScale    = MatrixToScale(mWorldMatrix);
    mWorldRotation = MatrixToRotation(mWorldMatrix, mWorldScale);
}

void Transform::AdoptTransformFromWorldValue()
{
    // world values > world matrix
    mWorldMatrix = ValuesToMatrix(mWorldScale, mWorldRotation, mWorldPosition);

    // world matrix > local matrix
    mLocalMatrix = glm::inverse(mParent->mWorldMatrix) * mWorldMatrix;

    // local matrix > local values
    mLocalPosition = MatrixToPosition(mLocalMatrix);
    mLocalScale    = MatrixToScale(mLocalMatrix);
    mLocalRotation = MatrixToRotation(mLocalMatrix, mLocalScale);
}

void Transform::AdoptTransformFromWorldMatrix()
{
    // world matrix > world values
    mWorldPosition = MatrixToPosition(mWorldMatrix);
    mWorldScale    = MatrixToScale(mWorldMatrix);
    mWorldRotation = MatrixToRotation(mWorldMatrix, mWorldScale);

    // world matrix > local matrix
    mLocalMatrix = glm::inverse(mParent->mWorldMatrix) * mWorldMatrix;

    // local matrix > local values
    mLocalPosition = MatrixToPosition(mLocalMatrix);
    mLocalScale    = MatrixToScale(mLocalMatrix);
    mLocalRotation = MatrixToRotation(mLocalMatrix, mLocalScale);
}

namespace {
Matrix4 ValuesToMatrix(Vector3 scale, Quaternion rotation, Vector3 position)
{
    // スケール行列
    Matrix4 scaleMatrix = Matrix4(1.0f); // 単位行列
    scaleMatrix[0][0]   = scale.x;       // X軸のスケール
    scaleMatrix[1][1]   = scale.y;       // Y軸のスケール

    // 回転行列
    Matrix4 rotationMatrix(1.0f);         // 単位行列
    rotationMatrix[0][0] = cos(rotation); // X軸の回転
    rotationMatrix[0][1] = -sin(rotation);
    rotationMatrix[1][0] = sin(rotation); // Y軸の回転
    rotationMatrix[1][1] = cos(rotation);

    // 平行移動行列
    Matrix4 translationMatrix = Matrix4(1.0f); // 単位行列
    translationMatrix[2][0]   = position.x;
    translationMatrix[2][1]   = position.y;

    // 順序：スケール → 回転 → 平行移動
    return translationMatrix * rotationMatrix * scaleMatrix;
}

Vector3 MatrixToPosition(Matrix4 mat)
{
    return Vector3(mat[0][2], mat[1][2]);
}

Vector3 MatrixToScale(Matrix4 mat)
{
    Vector3 scale;
    scale.x = glm::length(Vector3(mat[0][0], mat[1][0]));
    scale.y = glm::length(Vector3(mat[0][1], mat[1][1]));
    return scale;
}

Quaternion MatrixToRotation(Matrix4 mat, Vector3 scale)
{
    mat[0][0] /= scale.x;
    mat[1][0] /= scale.x;
    mat[0][1] /= scale.y;
    mat[1][1] /= scale.y;
    return atan2(mat[1][0], mat[0][0]);
}
}