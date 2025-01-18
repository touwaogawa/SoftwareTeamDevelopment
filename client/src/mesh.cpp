#include "mesh.h"
#include "renderer.h"
#include <glm/glm.hpp>
#include <iostream>
#include <string>
#include <tiny_obj_loader.h>
#include <vector>
Mesh::Mesh()
{
}
Mesh::~Mesh()
{
    delete mVertexArray;
}

// bool Mesh::LoadObjFile(const std::string& fileName)
// {
//     // tinyobjのオブジェクト作成
//     tinyobj::ObjReader reader;
//     if (!reader.ParseFromFile(fileName)) {
//         if (!reader.Error().empty()) {
//             std::cerr << "Error loading OBJ file: " << reader.Error() << std::endl;
//         }
//         return false;
//     }

//     // モデルデータを取得
//     const auto& shapes = reader.GetShapes();
//     const auto& attrib = reader.GetAttrib();
//     std::vector<Vertex> vertices;

//     // 頂点データとインデックスデータをVBOとEBO用に整理
//     for (size_t i = 0; i < shapes.size(); ++i) {
//         const auto& shape = shapes[i];
//         for (size_t j = 0; j < shape.mesh.indices.size(); ++j) {
//             const auto& idx = shape.mesh.indices[j];

//             glm::vec3 position = {
//                 attrib.vertices[idx.vertex_index * 3],
//                 attrib.vertices[idx.vertex_index * 3 + 1],
//                 attrib.vertices[idx.vertex_index * 3 + 2]
//             };
//             glm::vec3 normal = {
//                 attrib.normals[idx.normal_index * 3],
//                 attrib.normals[idx.normal_index * 3 + 1],
//                 attrib.normals[idx.normal_index * 3 + 2]
//             };
//             glm::vec2 texCoord = {
//                 attrib.texcoords[idx.texcoord_index * 2],
//                 attrib.texcoords[idx.texcoord_index * 2 + 1],
//             };
//             // Not gonna care about texCoord right now.
//             Vertex vert = { position, normal, texCoord };
//             vertices.push_back(vert);
//         }
//     }
//     mVertexArray = new VertexArray(vertices.data(), vertices.size(), VertexArray::Layout::PosNormTex);
//     return true;
// }

bool Mesh::LoadObjFile(const std::string& fileName)
{
    // tinyobjのオブジェクト作成
    tinyobj::ObjReader reader;
    if (!reader.ParseFromFile(fileName)) {
        if (!reader.Error().empty()) {
            std::cerr << "Error loading OBJ file: " << reader.Error() << std::endl;
        }
        return false;
    }

    // モデルデータを取得
    const auto& shapes = reader.GetShapes();
    const auto& attrib = reader.GetAttrib();
    std::vector<Vertex> vertices;

    // 頂点データとインデックスデータをVBOとEBO用に整理
    for (size_t i = 0; i < shapes.size(); ++i) {
        const auto& shape = shapes[i];
        for (size_t j = 0; j < shape.mesh.indices.size(); ++j) {
            const auto& idx = shape.mesh.indices[j];

            glm::vec3 position = {
                attrib.vertices[idx.vertex_index * 3],
                attrib.vertices[idx.vertex_index * 3 + 1],
                attrib.vertices[idx.vertex_index * 3 + 2]
            };

            // 座標系の変換
            position.z = -position.z; // Z軸反転

            glm::vec3 normal = {
                attrib.normals[idx.normal_index * 3],
                attrib.normals[idx.normal_index * 3 + 1],
                attrib.normals[idx.normal_index * 3 + 2]
            };

            // 法線のZ軸反転
            normal.z = -normal.z;

            glm::vec2 texCoord = {
                attrib.texcoords[idx.texcoord_index * 2],
                attrib.texcoords[idx.texcoord_index * 2 + 1],
            };

            // UV座標のY軸反転
            texCoord.y = 1.0f - texCoord.y;

            Vertex vert = { position, normal, texCoord };
            vertices.push_back(vert);
        }
    }
    mVertexArray = new VertexArray(vertices.data(), vertices.size(), VertexArray::Layout::PosNormTex);
    return true;
}

Texture* Mesh::GetTexture(size_t index)
{
    if (index < mTextures.size()) {
        return mTextures[index];
    } else {
        return nullptr;
    }
}
