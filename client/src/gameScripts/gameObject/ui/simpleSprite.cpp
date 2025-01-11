#include "simpleSprite.h"
#include "../../../../../common/src/component/transform.h"
#include "../../../component/spriteRenderer.h"
#include "../../../renderer.h"

SimpleSprite::SimpleSprite(Scene* scene, Transform* parent, const Matrix4& initialTransform, const std::string& fileName)
    : GameObject(scene, parent, nullptr)
{
    mTransform->SetWorldMatrix(initialTransform);
    // sprite
    SpriteRenderer* sprite = new SpriteRenderer(this);
    sprite->SetTexture(Renderer::GetTexture(fileName));
    AddComponent(sprite);
    // sprite->SetFrameSize(Vector2(1.0f, 1.0f));
    // sprite->SetFrameIndex(Vector2(0, 0));
    sprite->SetUseCustomColor(false);
}

SimpleSprite::~SimpleSprite() { }