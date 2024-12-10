#include "shader.h"
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

// 立方体の頂点データ
float vertices[] = {
    // 位置            // 法線
    -0.5f,
    -0.5f,
    -0.5f,
    0.0f,
    0.0f,
    -1.0f,
    0.5f,
    -0.5f,
    -0.5f,
    0.0f,
    0.0f,
    -1.0f,
    0.5f,
    0.5f,
    -0.5f,
    0.0f,
    0.0f,
    -1.0f,
    -0.5f,
    0.5f,
    -0.5f,
    0.0f,
    0.0f,
    -1.0f,

    -0.5f,
    -0.5f,
    0.5f,
    0.0f,
    0.0f,
    1.0f,
    0.5f,
    -0.5f,
    0.5f,
    0.0f,
    0.0f,
    1.0f,
    0.5f,
    0.5f,
    0.5f,
    0.0f,
    0.0f,
    1.0f,
    -0.5f,
    0.5f,
    0.5f,
    0.0f,
    0.0f,
    1.0f,

    -0.5f,
    0.5f,
    0.5f,
    -1.0f,
    0.0f,
    0.0f,
    -0.5f,
    0.5f,
    -0.5f,
    -1.0f,
    0.0f,
    0.0f,
    -0.5f,
    -0.5f,
    -0.5f,
    -1.0f,
    0.0f,
    0.0f,
    -0.5f,
    -0.5f,
    0.5f,
    -1.0f,
    0.0f,
    0.0f,

    0.5f,
    0.5f,
    0.5f,
    1.0f,
    0.0f,
    0.0f,
    0.5f,
    0.5f,
    -0.5f,
    1.0f,
    0.0f,
    0.0f,
    0.5f,
    -0.5f,
    -0.5f,
    1.0f,
    0.0f,
    0.0f,
    0.5f,
    -0.5f,
    0.5f,
    1.0f,
    0.0f,
    0.0f,

    -0.5f,
    -0.5f,
    -0.5f,
    0.0f,
    -1.0f,
    0.0f,
    0.5f,
    -0.5f,
    -0.5f,
    0.0f,
    -1.0f,
    0.0f,
    0.5f,
    -0.5f,
    0.5f,
    0.0f,
    -1.0f,
    0.0f,
    -0.5f,
    -0.5f,
    0.5f,
    0.0f,
    -1.0f,
    0.0f,

    -0.5f,
    0.5f,
    -0.5f,
    0.0f,
    1.0f,
    0.0f,
    0.5f,
    0.5f,
    -0.5f,
    0.0f,
    1.0f,
    0.0f,
    0.5f,
    0.5f,
    0.5f,
    0.0f,
    1.0f,
    0.0f,
    -0.5f,
    0.5f,
    0.5f,
    0.0f,
    1.0f,
    0.0f,
};

// インデックスデータ
unsigned int indices[] = {
    0, 1, 2, 2, 3, 0,
    4, 5, 6, 6, 7, 4,
    8, 9, 10, 10, 11, 8,
    12, 13, 14, 14, 15, 12,
    16, 17, 18, 18, 19, 16,
    20, 21, 22, 22, 23, 20
};
float window_w = 1920.0f;
float window_h = 1080.0f;
int main()
{
    // SDLの初期化
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("OpenGL Cube", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, static_cast<int>(window_w), static_cast<int>(window_h), SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (!window) {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_GLContext context = SDL_GL_CreateContext(window);
    if (!context) {
        std::cout << "OpenGL context could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cout << "GLEW initialization failed!" << std::endl;
        return -1;
    }

    Shader shader("vertex_shader.glsl", "fragment_shader.glsl");

    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // 投影行列
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), window_w / window_h, 0.1f, 100.0f);
    // ビュー行列
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f));
    // モデル行列
    glm::mat4 model = glm::mat4(1.0f);
    model           = glm::rotate(model, glm::radians(20.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    bool frag = true;
    while (frag) {
        SDL_Event e;
        if (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                frag = false;
                break;
            }
            if (e.type == SDL_KEYDOWN) {

                if (e.key.keysym.sym == SDLK_ESCAPE) {
                    frag = false;
                    break;
                }
                if (e.key.keysym.sym == SDLK_w) {
                    model *= glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -1.0f));
                }
                if (e.key.keysym.sym == SDLK_s) {
                    model *= glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
                }
                if (e.key.keysym.sym == SDLK_a) {
                    model *= glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
                }
                if (e.key.keysym.sym == SDLK_d) {
                    model *= glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                }
            }
            if (e.type == SDL_WINDOWEVENT) {
                if (e.window.event == SDL_WINDOWEVENT_RESIZED) {
                    window_w   = e.window.data1;
                    window_h   = e.window.data2;
                    projection = glm::perspective(glm::radians(45.0f), window_w / window_h, 0.1f, 100.0f);
                }
            }
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        shader.Use();
        GLint modelLoc = glGetUniformLocation(shader.Program, "model");
        GLint viewLoc  = glGetUniformLocation(shader.Program, "view");
        GLint projLoc  = glGetUniformLocation(shader.Program, "projection");

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        glm::mat4 secondModel = glm::mat4(4.0f);
        secondModel           = glm::rotate(secondModel, glm::radians(20.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        secondModel           = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -2.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(secondModel));
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);

        // ライトのプロパティ
        glUniform3f(glGetUniformLocation(shader.Program, "lightPos"), 1.2f, 4.0f, 2.0f);
        glUniform3f(glGetUniformLocation(shader.Program, "viewPos"), view[3][0], view[3][1], view[3][2]);

        // 色の設定
        glUniform3f(glGetUniformLocation(shader.Program, "lightColor"), 1.0f, 1.0f, 1.0f);
        glUniform3f(glGetUniformLocation(shader.Program, "objectColor"), 0.4f, 0.5f, 0.31f);

        // アンビエントライトの強度
        glUniform1f(glGetUniformLocation(shader.Program, "ambientStrength"), 0.6f);

        SDL_GL_SwapWindow(window);
        SDL_Delay(10);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
