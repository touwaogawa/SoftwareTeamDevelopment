#pragma once

#include "component.h"
#include <glm/glm.hpp>
#include <iostream>
#include <vector>

class Transform2 : public Component {
public:
    Transform2(GameObject* owner, Transform2* parent);
    ~Transform2();

    // getter setter local
    const glm::vec2& GetLocalPosition() const;
    void SetLocalPosition(glm::vec2 position);
    float GetLocaRotation() const;
    void SetLocalRotation(float rotation);
    const glm::vec2& GetLocalScale() const;
    void SetLocalScale(glm::vec2 scale);
    const glm::mat3& GetLocalMatrix() const;
    void SetLocalMatrix(glm::mat3 matrix);

    // getter setter world
    const glm::vec2& GetWorldPosition() const;
    void SetWorldPosition(glm::vec2 position);
    float GetLocaRotation() const;
    void SetWorldRotation(float rotation);
    const glm::vec2& GetWorldScale() const;
    void SetWorldScale(glm::vec2 scale);
    const glm::mat3& GetWorldMatrix() const;
    void SetWorldMatrix(glm::mat3 matrix);

    // 親子関係
    Transform2* GetParent() const;
    void MoveParent(Transform2* parent);
    std::vector<Transform2*> GetChildren() const;

private:
    // local values
    glm::vec2 mLocalPosition;
    float mLocalRotation;
    glm::vec2 mLocalScale;

    // local matrix
    glm::mat3 mLocalMatrix;

    // world values
    glm::vec2 mWorldPosition;
    float mWorldRotation;
    glm::vec2 mWorldScale;

    // world matrix
    glm::mat3 mWorldMatrix;

    // 親子関係
    Transform2* mParent;                // 親
    std::vector<Transform2*> mChildren; // 子(複数)

    // 親子関係
    void AddChild(Transform2* child);
    void RemoveChild(Transform2* child);

    // TransfomFrom
    void AdoptTransformFromLocalValue();
    void AdoptTransformFromLocalMatrix();
    void AdoptTransformFromWorldValue();
    void AdoptTransformFromWorldMatrix();
};