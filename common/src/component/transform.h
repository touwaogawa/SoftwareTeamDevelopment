#pragma once
#include "../../../utils/src/math.h"
#include "../component.h"
#include <vector>
class Transform : public Component {
public:
    Transform(class GameObject* owner);
    ~Transform() override;

    Transform* GetParent() const { return mParent; }
    void SetParent(Transform* parent, bool instantiateInWorldSpace = true);
    std::vector<Transform*> GetChildren() { return mChildren; }

    // ワールド
    Matrix4 GetWorldMatrix() const { return mWorldMatrix; }
    void SetWorldMatrix(Matrix4 matrix);
    Vector3 GetWorldPosition() const { return mWorldPosition; }
    void SetWorldPosition(Vector3 position);
    void SetWorldPosition(float x, float y, float z);
    Vector3 GetWorldScale() const { return mWorldScale; }
    void SetWorldScale(float x, float y, float z);
    void SetWorldScale(Vector3 scale);
    void SetWorldScale(float scale);
    Quaternion GetWorldRotation() const { return mWorldRotation; }
    void SetWorldRotation(Quaternion rotation);
    Vector3 GetWorldEulerAngles() const { return mWorldEulerAngles; }
    void SetWorldEulerAngles(Vector3 eulerAngles);
    void TransformationWorldMatrix(Matrix4 translationMat);

    // ローカル
    Matrix4 GetLocalMatrix() const { return mLocalMatrix; }
    void SetLocalMatrix(Matrix4 matrix);
    Vector3 GetLocalPosition() const { return mLocalPosition; }
    void SetLocalPosition(Vector3 position);
    void SetLocalPosition(float x, float y, float z);
    Vector3 GetLocalScale() const { return mLocalScale; }
    void SetLocalScale(float x, float y, float z);
    void SetLocalScale(Vector3 scale);
    void SetLocalScale(float scale);
    Quaternion GetLocalRotation() const { return mLocalRotation; }
    void SetLocalRotation(Quaternion rotation);
    Vector3 GetLocalEulerAngles() const { return mLocalEulerAngles; }
    void SetLocalEulerAngles(Vector3 eulerAngles);
    void TransformationLocalMatrix(Matrix4 translationMat);

private:
    void Enable() override { mIsOwnerActive = true; }
    void Disable() override { mIsOwnerActive = false; }
    bool mIsOwnerActive;

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
    void AdoptParentTransformForAllChildren();

    static void ConvertMatrixToValues(
        const Matrix4& matrix,
        Vector3& posOut,
        Quaternion& rotOut,
        Vector3& scaleOut,
        Vector3& eulerAngleOut);

    void RemoveChild(Transform* child);
    void AddChild(Transform* child) { mChildren.push_back(this); }
};