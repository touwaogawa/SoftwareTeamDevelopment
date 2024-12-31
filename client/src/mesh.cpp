#include "mesh.h"
#include <fstream>
#include <glm/glm.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
Mesh::Mesh()
{
}
Mesh::~Mesh()
{
    delete mVertexArray;
}

bool Mesh::LoadObjFile(const std::string& fileName)
{
    std::vector<float> verts;
    std::vector<unsigned int> indices;

    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Error opening file! :" << fileName << std::endl;
        return false;
    }

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> texCoords;
    std::vector<glm::ivec3> faceIdxs;

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string prefix;
        ss >> prefix;

        if (prefix == "v") { // 頂点
            glm::vec3 vertex;
            ss >> vertex.x >> vertex.y >> vertex.z;
            vertices.push_back(vertex);
        } else if (prefix == "vn") { // 法線
            glm::vec3 normal;
            ss >> normal.x >> normal.y >> normal.z;
            normals.push_back(normal);
        } else if (prefix == "vt") { // テクスチャ座標
            glm::vec2 texCoord;
            ss >> texCoord.x >> texCoord.y;
            texCoords.push_back(texCoord);
        } else if (prefix == "f") { // 面
            std::string faces[3];
            ss >> faces[0] >> faces[1] >> faces[2];

            for (std::string face : faces) {
                std::stringstream faceStream(face);
                std::string vIndex, vtIndex, vnIndex;
                std::getline(faceStream, vIndex, '/');
                std::getline(faceStream, vtIndex, '/');
                std::getline(faceStream, vnIndex, '/');

                glm::ivec3 faceIdx;
                faceIdx.x = std::stoi(vIndex);  // 頂点
                faceIdx.y = std::stoi(vtIndex); // UV
                faceIdx.z = std::stoi(vnIndex); // 法線

                faceIdxs.push_back(faceIdx);
            }
        }
    }
    int idx = 0;
    for (glm::ivec3 faceIdx : faceIdxs) {
        // 頂点
        verts.push_back(vertices[faceIdx.x - 1].x);
        verts.push_back(vertices[faceIdx.x - 1].y);
        verts.push_back(vertices[faceIdx.x - 1].z);
        // 法線
        verts.push_back(normals[faceIdx.z - 1].x);
        verts.push_back(normals[faceIdx.z - 1].y);
        verts.push_back(normals[faceIdx.z - 1].z);
        // UV
        verts.push_back(texCoords[faceIdx.y - 1].x);
        verts.push_back(texCoords[faceIdx.y - 1].y);
        //  indicesには頂点情報を使う
        indices.push_back(idx++);
    }

    mNumVerts    = verts.size() / 8;
    mVertexArray = new VertexArray(verts.data(), verts.size() / 8, VertexArray::Layout::PosNormTex, indices.data(), indices.size());

    file.close();
    return true;
}

VertexArray* Mesh::GetVAO() const
{
    return mVertexArray;
}