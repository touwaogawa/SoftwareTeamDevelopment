#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

// 頂点構造体
struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

// MTLファイルの読み込み
std::map<std::string, GLuint> LoadMTL(const std::string &mtlFile)
{
    std::map<std::string, GLuint> textures;
    std::ifstream file(mtlFile);
    std::string line;

    GLuint currentTexture = 0;

    while (getline(file, line)) {
        if (line.substr(0, 6) == "newmtl") {
            std::string textureName = line.substr(7);
            // 新しいマテリアルがあれば、テクスチャを読み込む
            currentTexture        = LoadTexture(textureName); // ここでテクスチャを読み込む関数を使う
            textures[textureName] = currentTexture;
        }
    }
    return textures;
}

// テクスチャの読み込み
GLuint LoadTexture(const std::string &filename)
{
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    int width, height, channels;
    unsigned char *image = SOIL_load_image(filename.c_str(), &width, &height, &channels, SOIL_LOAD_AUTO);
    if (image == nullptr) {
        std::cerr << "Failed to load texture: " << filename << std::endl;
        return 0;
    }

    GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return textureID;
}

// OBJファイルの読み込み
std::vector<Vertex> LoadOBJ(const std::string &objFile)
{
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::map<std::string, GLuint> textures;
    std::ifstream file(objFile);
    std::string line;

    std::vector<glm::vec3> positions;
    std::vector<glm::vec2> texCoords;
    std::vector<glm::vec3> normals;

    while (getline(file, line)) {
        std::istringstream s(line);
        std::string prefix;
        s >> prefix;

        if (prefix == "v") {
            glm::vec3 position;
            s >> position.x >> position.y >> position.z;
            positions.push_back(position);
        } else if (prefix == "vt") {
            glm::vec2 texCoord;
            s >> texCoord.x >> texCoord.y;
            texCoords.push_back(texCoord);
        } else if (prefix == "vn") {
            glm::vec3 normal;
            s >> normal.x >> normal.y >> normal.z;
            normals.push_back(normal);
        } else if (prefix == "f") {
            GLuint idx[3];
            for (int i = 0; i < 3; i++) {
                std::string vertex;
                s >> vertex;
                sscanf(vertex.c_str(), "%d/%d/%d", &idx[i], &idx[i], &idx[i]);
                Vertex v;
                v.position  = positions[idx[i] - 1];
                v.normal    = normals[idx[i] - 1];
                v.texCoords = texCoords[idx[i] - 1];
                vertices.push_back(v);
            }
        }
    }

    return vertices;
}

int main()
{
    // GLFWの初期化
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // ウィンドウ作成
    GLFWwindow *window = glfwCreateWindow(800, 600, "OBJ Loader", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glewInit();

    // OBJとMTLの読み込み
    std::string objFile = "model.obj";
    std::string mtlFile = "model.mtl";
    auto vertices       = LoadOBJ(objFile);
    auto textures       = LoadMTL(mtlFile);

    // OpenGLの描画ループ
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // シェーダ、VAOの設定やテクスチャのバインディングを行う

        // 頂点を描画
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
