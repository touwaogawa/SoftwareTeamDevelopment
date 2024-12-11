#include "shader.h"
#include <fstream>
#include <iostream>
#include <sstream>
Shader::Shader()
{
}
bool Shader::Load(const std::string& vertexPath, const std::string& fragmentPath)
{
    // シェーダーコードの読み込み、コンパイル
    GLuint vertex, fragment;
    if (!CompileShader(vertexPath, GL_VERTEX_SHADER, vertex))
        return false;
    if (!CompileShader(fragmentPath, GL_FRAGMENT_SHADER, fragment))
        return false;

    // シェーダープログラムのリンク
    mProgram = glCreateProgram();
    glAttachShader(mProgram, vertex);
    glAttachShader(mProgram, fragment);
    glLinkProgram(mProgram);
    if (!checkCompileErrors(mProgram, 0))
        return false;

    // シェーダーの削除
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return true;
}

void Shader::Use()
{
    glUseProgram(mProgram);
}
GLuint Shader::GetProgram() const
{
    return mProgram;
}
bool Shader::checkCompileErrors(GLuint shader, GLenum shaderType)
{
    GLint success;
    GLchar infoLog[1024];
    if (shaderType == GL_VERTEX_SHADER || shaderType == GL_FRAGMENT_SHADER) {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of shaderType: " << shaderType << "\n"
                      << infoLog << "\n";
            return false;
        }
    } else {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of shaderType: " << shaderType << "\n"
                      << infoLog << "\n";
            return false;
        }
    }
    return true;
}

bool Shader::CompileShader(const std::string& fileName,
    GLenum shaderType,
    GLuint& outShader)
{
    std::string code;
    std::ifstream shaderFile(fileName);
    if (shaderFile.is_open()) {
        std::stringstream shaderStream;

        shaderStream << shaderFile.rdbuf();
        code = shaderStream.str();

        const char* charCode = code.c_str();

        outShader = glCreateShader(shaderType);
        glShaderSource(outShader, 1, &charCode, NULL);
        glCompileShader(outShader);
        if (!checkCompileErrors(outShader, shaderType))
            return false;
    } else {
        std::cerr << "Error: Could not open file " << fileName << std::endl;
        return false;
    }
    return true;
}