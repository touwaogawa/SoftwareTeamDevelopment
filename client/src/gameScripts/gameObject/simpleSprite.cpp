#include "simpleSprite.h"
#include "../../../../common/src/component/transform.h"
#include "../../component/spriteRenderer.h"
#include "../../renderer.h"

SimpleSprite::SimpleSprite(const std::string& fileName)
    : GameObject()
{
    // sprite
    SpriteRenderer* sprite = new SpriteRenderer(this);
    sprite->SetTexture(Renderer::GetTexture(fileName));
    AddComponent(sprite);
}