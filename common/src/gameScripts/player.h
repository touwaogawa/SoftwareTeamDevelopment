#pragma once

#include "../../../common/src/gameObject.h"
#include "../commandData.h"
#include <deque>

class Player : public GameObject {
public:
    Player(Scene* scene, Transform* parent, int playerID);
    ~Player() override;

    std::deque<CommandData> commandBuffer;
    CommandData prevCommandData;
    class Hero* GetHero() const;
    int GetID() const;

private:
    class Hero* mHero;
    int mID;
};