#pragma once

#include "../commandData.h"
#include "../gameObject.h"
#include <deque>

class Player : public GameObject {
public:
    Player(Scene* scene, Transform* parent);
    ~Player() override;

    std::deque<CommandData> commandBuffer;

private:
    GameObject* mHero;
    int mID;
};