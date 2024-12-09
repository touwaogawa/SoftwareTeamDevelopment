#pragma once

#include "../components/transform_component.h"
#include <string>

class GameObject {
public:
    GameObject(GameObject* parent = nullptr, std::string name = "GameObject");
    ~GameObject();

    std::string name; // オブジェクト名
    std::string tag;  // タグ

    // コンポーネント
    Transform transform; // トランスフォームコンポーネント

    template <typename T>
    T& GetComponent() const;

    void AddComponent(Component* component);

    bool GetActive() const;
    void SetActive();

private:
    bool isActive;
    std::vector<Component*> mComponentList;
};