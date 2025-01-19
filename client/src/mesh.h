#pragma once
#include "vertexArray.h"
#include <string>

class Texture;
class Mesh {
public:
    Mesh();
    ~Mesh();
    bool LoadObjFile(const std::string& fileName);
    int SetTexture(Texture* texture)
    {
        auto it = std::find(mTextures.begin(), mTextures.end(), texture);

        if (it != mTextures.end()) {
            // 見つかった場合、インデックスを返す
            return std::distance(mTextures.begin(), it);
        } else {
            // 見つからなかった場合、追加してインデックスを返す
            mTextures.push_back(texture);
            return mTextures.size() - 1; // 新しい要素のインデックス
        }
    }
    VertexArray* GetVertexArray() const { return mVertexArray; }
    Texture* GetTexture(size_t index);

private:
    VertexArray* mVertexArray;
    std::vector<Texture*> mTextures;
};