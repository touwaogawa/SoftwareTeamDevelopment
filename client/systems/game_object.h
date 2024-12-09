#pragma once

#include "object.h"
#include <vector>
class GameObject : public Object {
public:
    GameObject(std::string name = "name");
    int layer;
    std::string tag;

private:
    class Transform& mTransform;
    std::vector<class Component&> mComponents;
};