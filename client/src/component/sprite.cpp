#include "sprite.h"
#include "../../../common/src/component/transform.h"
#include "../../../common/src/gameObject.h"
#include "../renderer.h"
#include "../shader.h"
#include "../texture.h"
#include <iostream>

Sprite::Sprite(GameObject* owner, int order)
    : Component(owner)
    , mDrawOrder(order)
    , mTexWidth(0)
    , mTexHeight(0)
    , mVisible(true)
{
    Renderer::AddSprite(this);
}

Sprite::~Sprite()
{
    // std::cout << "~Sprite" << std::endl;
    Renderer::RemoveSprite(this);
}

void Sprite::Draw(Shader* shader)
{
    if (mTexture) {
        // Scale the quad by the width/height of texture
        Matrix4 scaleMat = Matrix4::CreateScale(
            static_cast<float>(mTexWidth),
            static_cast<float>(mTexHeight),
            1.0f);

        Matrix4 model = scaleMat * mOwner->GetTransform()->GetWorldMatrix();

        // Since all sprites use the same shader/vertices,
        // the game first sets them active before any sprite draws

        // Set world transform
        shader->SetMatrixUniform("model", model);
        // Set current texture
        mTexture->SetActive();
        // Draw quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
}
void Sprite::SetTexture(Texture* texture)
{
    mTexture = texture;
    // Set width/height
    mTexWidth  = texture->GetWidth();
    mTexHeight = texture->GetHeight();
}