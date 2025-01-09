#include "title.h"
#include "../../../component/sprite.h"
#include "../../../renderer.h"
#include <iostream>

TitleUI::TitleUI(Scene* scene, Transform* parent)
    : GameObject(scene, parent)
{
    Sprite* sprite = new Sprite(this);

    sprite->SetTexture(Renderer::GetTexture("../assets/textures/title.png"));
    AddComponent(sprite);
}

TitleUI::~TitleUI()
{
    std::cout << "title dest " << std::endl;
}