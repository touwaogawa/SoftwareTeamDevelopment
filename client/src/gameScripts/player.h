#pragma once

#include "../commandData.h"
#include "../gameObject.h"
#include <deque>

class Player : public GameObject {
public:
    Player(Scene* scene, Transform* parent, int playerID);
    ~Player() override;

    std::deque<CommandData> commandBuffer;
    CommandData prevCommandData;
    GameObject* GetHero() const;
    int GetID() const;

private:
    GameObject* mHero;
    int mID;
};