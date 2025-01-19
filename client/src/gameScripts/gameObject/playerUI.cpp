#include "playerUI.h"
#include "../../../../common/src/component/transform.h"
#include "../../renderer.h"
#include "simpleSprite.h"
#include <iostream>

PlayerUI::PlayerUI(int playerID)
    : GameObject("PlayerUI")
{
    SimpleSprite *bg, *icon;
    switch (playerID) {
    case 0: {
        bg   = new SimpleSprite("../assets/textures/battleScene/iconBackground_1.png");
        icon = new SimpleSprite("../assets/textures/battleScene/humanIcon_red.png");
    } break;
    case 1: {

        bg   = new SimpleSprite("../assets/textures/battleScene/iconBackground_2.png");
        icon = new SimpleSprite("../assets/textures/battleScene/humanIcon_blue.png");
    } break;
    case 2: {

        bg   = new SimpleSprite("../assets/textures/battleScene/iconBackground_3.png");
        icon = new SimpleSprite("../assets/textures/battleScene/humanIcon_green.png");
    } break;
    case 3: {

        bg   = new SimpleSprite("../assets/textures/battleScene/iconBackground_4.png");
        icon = new SimpleSprite("../assets/textures/battleScene/humanIcon_yellow.png");
    } break;
    default: {
        std::cout << "PlayerUI : player id error " << std::endl;
    } break;
    }
    bg->GetTransform()->SetParent(GetTransform(), false);
    icon->GetTransform()->SetParent(GetTransform(), false);
}
