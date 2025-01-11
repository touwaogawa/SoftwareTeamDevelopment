#include "titleUI.h"
#include "../../../../../utils/src/math.h"
#include "../../../audio.h"
#include "../../../component/spriteRenderer.h"
#include "../../../renderer.h"
#include <iostream>

TitleUI::TitleUI(Scene* scene, Transform* parent)
    : GameObject(scene, parent)
{
    // sprite
    SpriteRenderer* sprite = new SpriteRenderer(this);
    sprite->SetTexture(Renderer::GetTexture("../assets/textures/title.png"));
    AddComponent(sprite);
    sprite->SetFrameSize(Vector2(1.0f, 1.0f));
    sprite->SetFrameIndex(Vector2(0, 0));
    sprite->SetUseCustomColor(false);

    // audio
    Audio::SetMusicVolume(0.4f);
    Audio::PlayMusic("../assets/sounds/bgm/Who_Is_the_Champion.mp3");
}

TitleUI::~TitleUI()
{
    std::cout << "titleui deleted" << std::endl;
}