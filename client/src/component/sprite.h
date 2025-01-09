#pragma once

#include "../../../common/src/component.h"
#include <string>

class GameObject;
class Texture;
class Shader;
class Sprite : public Component {
public:
    Sprite(GameObject* owner, int order = 0);
    ~Sprite();

    void Draw(Shader* shader);
    void SetTexture(Texture* texture);

    int GetDrawOrder() const { return mDrawOrder; }
    int GetTexHeight() const { return mTexHeight; }
    int GetTexWidth() const { return mTexWidth; }

    void SetVisible(bool visible) { mVisible = visible; }
    bool GetVisible() const { return mVisible; }

private:
    Texture* mTexture;
    int mDrawOrder;
    int mTexWidth;
    int mTexHeight;
    bool mVisible;
};
