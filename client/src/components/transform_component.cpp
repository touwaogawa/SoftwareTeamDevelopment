#include "transform_component.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace {
glm::mat3 ValuesToMatrix(glm::vec2 scale, float rotation, glm::vec2 position);
glm::vec2 MatrixToPosition(glm::mat3 mat);
glm::vec2 MatrixToScale(glm::mat3 mat);
float MatrixToRotation(glm::mat3 mat, glm::vec2 scale);
}

Transform2::Transform2(GameObject* owner, Transform2* parent)
    : Component(owner)
    , mParent(parent) // 親を設定
{
    if (mParent != nullptr) {
        // 親に自分を子として設定してもらう
        mParent->mChildren.push_back(this);
    }
}
Transform2::~Transform2()
{
    mParent->RemoveChild(this);
}

// getter setter local
const glm::vec2& Transform2::GetLocalPosition() const
{
    return mLocalPosition;
}
void Transform2::SetLocalPosition(glm::vec2 position)
{
    mLocalPosition = position;
    AdoptTransformFromLocalValue();
    for (Transform2* child : mChildren) {
        child->AdoptTransformFromLocalValue();
    }
}
float Transform2::GetLocaRotation() const
{
    return mLocalRotation;
}
void Transform2::SetLocalRotation(float rotation)
{
    mLocalRotation = rotation;
    AdoptTransformFromLocalValue();
    for (Transform2* child : mChildren) {
        child->AdoptTransformFromLocalValue();
    }
}
const glm::vec2& Transform2::GetLocalScale() const
{
    return mLocalScale;
}
void Transform2::SetLocalScale(glm::vec2 scale)
{
    mLocalScale = scale;
    AdoptTransformFromLocalValue();
    for (Transform2* child : mChildren) {
        child->AdoptTransformFromLocalValue();
    }
}
const glm::mat3& Transform2::GetLocalMatrix() const
{
    return mLocalMatrix;
}
void Transform2::SetLocalMatrix(glm::mat3 matrix)
{
    mLocalMatrix = matrix;
    AdoptTransformFromLocalMatrix();
    for (Transform2* child : mChildren) {
        child->AdoptTransformFromLocalValue();
    }
}

// getter setter world
const glm::vec2& Transform2::GetWorldPosition() const
{
    return mWorldPosition;
}
void Transform2::SetWorldPosition(glm::vec2 position)
{
    mWorldPosition = position;
    AdoptTransformFromWorldValue();
    for (Transform2* child : mChildren) {
        child->AdoptTransformFromLocalValue();
    }
}
float Transform2::GetLocaRotation() const
{
    return mWorldRotation;
}
void Transform2::SetWorldRotation(float rotation)
{
    mWorldRotation = rotation;
    AdoptTransformFromWorldValue();
    for (Transform2* child : mChildren) {
        child->AdoptTransformFromLocalValue();
    }
}
const glm::vec2& Transform2::GetWorldScale() const
{
    return mWorldScale;
}
void Transform2::SetWorldScale(glm::vec2 scale)
{
    mWorldScale = scale;
    AdoptTransformFromWorldValue();
    for (Transform2* child : mChildren) {
        child->AdoptTransformFromLocalValue();
    }
}
const glm::mat3& Transform2::GetWorldMatrix() const
{
    return mWorldMatrix;
}
void Transform2::SetWorldMatrix(glm::mat3 matrix)
{
    mWorldMatrix = matrix;
    AdoptTransformFromWorldMatrix();
    for (Transform2* child : mChildren) {
        child->AdoptTransformFromLocalValue();
    }
}
void Transform2::MoveParent(Transform2* parent)
{
    if (mParent != nullptr) {
        mParent->RemoveChild(this);
    }
    mParent = parent;
    mParent->AddChild(this);
    AdoptTransformFromWorldValue(); // localの値を新しい親を基準に再設定
}

// 親子関係public
Transform2* Transform2::GetParent() const
{
    return mParent;
}
void MoveParent(Transform2* parent)
{
}

std::vector<Transform2*> Transform2::GetChildren() const
{
    return mChildren;
}

// 親子関係private
void Transform2::AddChild(Transform2* child)
{
    mChildren.push_back(child);
}

//
void Transform2::AdoptTransformFromLocalValue()
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

void Transform2::AdoptTransformFromLocalMatrix()
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

void Transform2::AdoptTransformFromWorldValue()
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

void Transform2::AdoptTransformFromWorldMatrix()
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
glm::mat3 ValuesToMatrix(glm::vec2 scale, float rotation, glm::vec2 position)
{
    // スケール行列
    glm::mat3 scaleMatrix = glm::mat3(1.0f); // 単位行列
    scaleMatrix[0][0]     = scale.x;         // X軸のスケール
    scaleMatrix[1][1]     = scale.y;         // Y軸のスケール

    // 回転行列
    glm::mat3 rotationMatrix(1.0f);       // 単位行列
    rotationMatrix[0][0] = cos(rotation); // X軸の回転
    rotationMatrix[0][1] = -sin(rotation);
    rotationMatrix[1][0] = sin(rotation); // Y軸の回転
    rotationMatrix[1][1] = cos(rotation);

    // 平行移動行列
    glm::mat3 translationMatrix = glm::mat3(1.0f); // 単位行列
    translationMatrix[2][0]     = position.x;
    translationMatrix[2][1]     = position.y;

    // 順序：スケール → 回転 → 平行移動
    return translationMatrix * rotationMatrix * scaleMatrix;
}

glm::vec2 MatrixToPosition(glm::mat3 mat)
{
    return glm::vec2(mat[0][2], mat[1][2]);
}

glm::vec2 MatrixToScale(glm::mat3 mat)
{
    glm::vec2 scale;
    scale.x = glm::length(glm::vec2(mat[0][0], mat[1][0]));
    scale.y = glm::length(glm::vec2(mat[0][1], mat[1][1]));
    return scale;
}

float MatrixToRotation(glm::mat3 mat, glm::vec2 scale)
{
    mat[0][0] /= scale.x;
    mat[1][0] /= scale.x;
    mat[0][1] /= scale.y;
    mat[1][1] /= scale.y;
    return atan2(mat[1][0], mat[0][0]);
}
}