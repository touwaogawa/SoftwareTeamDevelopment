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
    Transform2 transform; // トランスフォームコンポーネント

private:
};