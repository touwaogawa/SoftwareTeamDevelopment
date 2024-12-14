#pragma once
#include "../component.h"
#include "../math.h"
#include <vector>
class Transform : public Component {
public:
    Transform(class GameObject* owner, Transform* parent = nullptr);
    ~Transform();

    Transform* GetParent() const;
    void SetParent(Transform* newParent);
    std::vector<Transform*> GetChildren();

    // ワールド
    Matrix4 GetWorldMatrix();
    void SetWorldMatrix(Matrix4 matrix);
    Vector3 GetWorldPosition();
    void SetWorldPosition(Vector3 position);
    void SetWorldPosition(float x, float y, float z);
    Vector3 GetWorldScale();
    void SetWorldScale(float x, float y, float z);
    void SetWorldScale(Vector3 scale);
    void SetWorldScale(float scale);
    Quaternion GetWorldRotation();
    void SetWorldRotation(Quaternion rotation);
    Vector3 GetWorldEulerAngles();
    void SetWorldEulerAngles(Vector3 eulerAngles);
    void TransformationWorldMatrix(Matrix4 translationMat);

    // ローカル
    Matrix4 GetLocalMatrix();
    void SetLocalMatrix(Matrix4 matrix);
    Vector3 GetLocalPosition();
    void SetLocalPosition(Vector3 position);
    void SetLocalPosition(float x, float y, float z);
    Vector3 GetLocalScale();
    void SetLocalScale(float x, float y, float z);
    void SetLocalScale(Vector3 scale);
    void SetLocalScale(float scale);
    Quaternion GetLocalRotation();
    void SetLocalRotation(Quaternion rotation);
    Vector3 GetLocalEulerAngles();
    void SetLocalEulerAngles(Vector3 eulerAngles);
    void TransformationLocalMatrix(Matrix4 translationMat);

private:
    Transform* mParent;
    std::vector<Transform*> mChildren;

    // ワールド
    Matrix4 mWorldMatrix;
    Vector3 mWorldPosition;
    Vector3 mWorldScale;
    Quaternion mWorldRotation;
    Vector3 mWorldEulerAngles;

    // ローカル
    Matrix4 mLocalMatrix;
    Vector3 mLocalPosition;
    Vector3 mLocalScale;
    Quaternion mLocalRotation;
    Vector3 mLocalEulerAngles;

    void AdoptfromWorldMatrix();
    void AdoptfromLocalMatrix();
    void AdoptfromWorldValue();
    void AdoptfromLocalValue();

    void AdoptParentTransform();
    static void ConvertMatrixToValues(
        const Matrix4& matrix,
        Vector3& posOut,
        Quaternion& rotOut,
        Vector3& scaleOut,
        Vector3& eulerAngleOut);

    void AddChild(Transform* child);
    void RemoveChild(Transform* child);
};