#include "shader.h"
#include "time.h"
#include "vertexArray.h"
#include "vertices.h"
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
// 立方体の頂点データ

float window_w = 1920.0f;
float window_h = 1080.0f;
int main(int argc, char* argv[])
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

    Shader shader;
    shader.Load("shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl");

    VertexArray cubeVAO(vertices, 36, VertexArray::Layout::PosNorm, indices, 36);

    // 投影行列
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), window_w / window_h, 0.1f, 100.0f);
    // ビュー行列
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f));
    // モデル行列1
    glm::mat4 model = glm::mat4(1.0f);
    model           = glm::rotate(model, glm::radians(20.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    // モデル行列2
    glm::mat4 secondModel  = glm::mat4(1.0f);
    glm::mat4 secondModelL = glm::mat4(1.0f);
    secondModelL           = glm::rotate(secondModelL, glm::radians(20.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    secondModelL *= glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -4.0f, 0.0f));
    secondModelL *= glm::scale(glm::mat4(1.0f), glm::vec3(10.0f, 2.0f, 10.0f));

    // ループ前処理
    SDL_Event e;
    Time::Init(60);
    const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
    bool frag                  = true;
    while (frag) {
        if (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                frag = false;
                break;
            }
            if (e.type == SDL_KEYDOWN /* && e.key.repeat == 0*/) {

                if (keyboardState[SDL_SCANCODE_ESCAPE]) {
                    frag = false;
                    break;
                }
                if (keyboardState[SDL_SCANCODE_W]) {
                    // 親モデル（model）の移動
                    model *= glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -1.0f));

                    secondModel = model * secondModelL;
                }
                if (keyboardState[SDL_SCANCODE_S]) {
                    // 親モデル（model）の移動
                    model *= glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 1.0f));

                    secondModel = model * secondModelL;
                }
                if (keyboardState[SDL_SCANCODE_A]) {
                    // 親モデル（model）の移動
                    model *= glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.0f, 0.0f));

                    secondModel = model * secondModelL;
                }
                if (keyboardState[SDL_SCANCODE_D]) {
                    // 親モデル（model）の移動
                    model *= glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 0.0f));

                    secondModel = model * secondModelL;
                }

                if (keyboardState[SDL_SCANCODE_Q]) {
                    model *= glm::rotate(glm::mat4(1.0f), glm::radians(20.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                    secondModel = model * secondModelL;
                }

                if (keyboardState[SDL_SCANCODE_UP]) {
                    secondModelL *= glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -1.0f) / 10.0f);
                    secondModel = model * secondModelL;
                }
                if (keyboardState[SDL_SCANCODE_DOWN]) {
                    secondModelL *= glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 1.0f) / 10.0f);
                    secondModel = model * secondModelL;
                }
                if (keyboardState[SDL_SCANCODE_LEFT]) {
                    secondModelL *= glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.0f, 0.0f) / 10.0f);
                    secondModel = model * secondModelL;
                }
                if (keyboardState[SDL_SCANCODE_RIGHT]) {
                    secondModelL *= glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 0.0f) / 10.0f);
                    secondModel = model * secondModelL;
                }
                if (keyboardState[SDL_SCANCODE_R]) {
                    secondModelL *= glm::rotate(glm::mat4(1.0f), glm::radians(20.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                    secondModel = model * secondModelL;
                }
                if (keyboardState[SDL_SCANCODE_T]) {
                    secondModelL *= glm::scale(glm::mat4(1.0f), glm::vec3(10.0f, 2.0f, 10.0f));
                    secondModel = model * secondModelL;
                }
                if (keyboardState[SDL_SCANCODE_Y]) {
                    secondModelL /= glm::scale(glm::mat4(1.0f), glm::vec3(10.0f, 2.0f, 10.0f));
                    secondModel = model * secondModelL;
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
        GLint modelLoc = glGetUniformLocation(shader.GetProgram(), "model");
        GLint viewLoc  = glGetUniformLocation(shader.GetProgram(), "view");
        GLint projLoc  = glGetUniformLocation(shader.GetProgram(), "projection");

        // model
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
        cubeVAO.Bind();
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        // secondModel
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(secondModel));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
        // cubeVAO.Bind();
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);

        // ライトのプロパティ
        glUniform3f(glGetUniformLocation(shader.GetProgram(), "lightPos"), 1.2f, 4.0f, 2.0f);
        glUniform3f(glGetUniformLocation(shader.GetProgram(), "viewPos"), view[3][0], view[3][1], view[3][2]);

        // 色の設定
        glUniform3f(glGetUniformLocation(shader.GetProgram(), "lightColor"), 1.0f, 1.0f, 1.0f);
        glUniform3f(glGetUniformLocation(shader.GetProgram(), "objectColor"), 0.4f, 0.5f, 0.31f);

        // アンビエントライトの強度
        glUniform1f(glGetUniformLocation(shader.GetProgram(), "ambientStrength"), 0.6f);

        SDL_GL_SwapWindow(window);
        Time::UpdateFrame();
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
