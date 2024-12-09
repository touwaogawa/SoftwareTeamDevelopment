#pragma once

#include "game_object.h"
#include "object.h"
class Component : public Object {
public:
    GameObject& gameObject;
    std::string& tag;

private:
};