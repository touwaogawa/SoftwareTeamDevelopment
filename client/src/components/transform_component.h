#pragma once

#include "../../common/src/common_math.h"
#include "component.h"
#include <iostream>
#include <vector>

class Transform : public Component {
public:
    Transform(GameObject* owner, Transform* parent);
    ~Transform();

    enum class Space {
        World,
        Self
    };

    // getter setter local
    const Vector3& GetLocalPosition() const;
    void SetLocalPosition(Vector3 position);
    Quaternion GetLocaRotation() const;
    void SetLocalRotation(Quaternion rotation);
    const Vector3& GetLocalScale() const;
    void SetLocalScale(Vector3 scale);
    const Matrix4& GetLocalMatrix() const;
    void SetLocalMatrix(Matrix4 matrix);

    // getter setter world
    const Vector3& GetWorldPosition() const;
    void SetWorldPosition(Vector3 position);
    Quaternion GetLocaRotation() const;
    void SetWorldRotation(Quaternion rotation);
    const Vector3& GetWorldScale() const;
    void SetWorldScale(Vector3 scale);
    const Matrix4& GetWorldMatrix() const;
    void SetWorldMatrix(Matrix4 matrix);

    // 指定した方向に移動させる
    void Translate(Vector3 translation);
    void Translate(Vector3 translation, Space relativeTo);
    void Translate(float x, float y, float z);
    void Translate(float x, float y, float z, Space relativeTo);
    // 指定した軸まわりに回転させる
    void Rotate(Vector3 a, float b);
    void Scale(Vector3 a);

    // 親子関係
    Transform* GetParent() const;
    void MoveParent(Transform* parent);
    std::vector<Transform*> GetChildren() const;

    void DetachChildren();

private:
    // local values
    Vector3 mLocalPosition;
    Quaternion mLocalRotation;
    Vector3 mLocalScale;

    // local matrix
    Matrix4 mLocalMatrix;

    // world values
    Vector3 mWorldPosition;
    Quaternion mWorldRotation;
    Vector3 mWorldScale;

    // world matrix
    Matrix4 mWorldMatrix;

    // 親子関係
    Transform* mParent;                // 親
    std::vector<Transform*> mChildren; // 子(複数)

    // 親子関係
    void AddChild(Transform* child);
    void RemoveChild(Transform* child);

    // TransfomFrom
    void AdoptTransformFromLocalValue();
    void AdoptTransformFromLocalMatrix();
    void AdoptTransformFromWorldValue();
    void AdoptTransformFromWorldMatrix();
};