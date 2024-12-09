#include "game_object.h"
#include "../components/transform_component.h"
#include <string>

GameObject::GameObject(GameObject* parent, std::string newName)
    : name(newName)
    , transform(this, &parent->transform)
{
}
GameObject::~GameObject()
{
}