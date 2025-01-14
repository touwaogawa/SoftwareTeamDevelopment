#include "playerMove.h"
#include "../../../../../common/src/gameObject.h"
#include <iostream>
PlayerMove_S::PlayerMove_S(GameObject* owner)
    : PlayerMove(owner)
{
    std::cout << "playerMove_s gen" << std::endl;
}