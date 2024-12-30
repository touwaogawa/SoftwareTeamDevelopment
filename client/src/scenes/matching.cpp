#include "matching.h"
#include "../../../common/src/sceneManager.h"
#include "../../../utils/src/input.h"
#include "../renderer.h"
#include "battle.h"
#include <iostream>
MatchingScene::MatchingScene()
    : Scene("MatchingScene")
    , mMatchingState(MatchingState::Connecting)
{
}

MatchingScene::~MatchingScene()
{
}

bool MatchingScene::Load()
{
    if (!Renderer::Load()) {
        std::cout << "Failed Renderer Load" << std::endl;
        return false;
    }
    return true;
}

void MatchingScene::BeforeUpdateGameObject()
{
    ProccessNetowork();
    ProccessInput();
}

void MatchingScene::AfterUpdateGameObject()
{
}

bool MatchingScene::ProccessInput()
{
    if (Input::GetKeyDown(SDL_SCANCODE_ESCAPE)) {
        return false;
    }
    int playerNum = 2;
    if (Input::GetKeyDown(SDL_SCANCODE_0)) {
        SceneManager::LoadScene(new BattleScene(0, playerNum));
    }
    if (Input::GetKeyDown(SDL_SCANCODE_1)) {
        SceneManager::LoadScene(new BattleScene(1, playerNum));
    }
    // if (Input::GetKeyDown(SDL_SCANCODE_2)) {
    //     SceneManager::LoadScene(new BattleScene(2, playerNum));
    // }
    // if (Input::GetKeyDown(SDL_SCANCODE_3)) {
    //     SceneManager::LoadScene(new BattleScene(3, playerNum));
    // }
    return true;
}

void MatchingScene::ProccessNetowork()
{
    switch (mMatchingState) {
    case MatchingState::Connecting:
        break;
    case MatchingState::Connected:
        break;
    default:
        std::cout << "MatchingState error" << std::endl;
        break;
    }
}