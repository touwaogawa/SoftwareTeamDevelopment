#include "shader.h"
#include "../../utils/src/math.h"
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

void Shader::SetMatrixUniform(const char* name, const Matrix4& matrix)
{
    // Find the uniform by this name
    GLuint loc = glGetUniformLocation(mProgram, name);
    // Send the matrix data to the uniform
    glUniformMatrix4fv(loc, 1, GL_TRUE, matrix.GetAsFloatPtr());
}

void Shader::SetMatrixUniforms(const char* name, Matrix4* matrices, unsigned count)
{
    GLuint loc = glGetUniformLocation(mProgram, name);
    // Send the matrix data to the uniform
    glUniformMatrix4fv(loc, count, GL_TRUE, matrices->GetAsFloatPtr());
}

void Shader::SetVectorUniform(const char* name, const Vector3& vector)
{
    GLuint loc = glGetUniformLocation(mProgram, name);
    // Send the vector data
    glUniform3fv(loc, 1, vector.GetAsFloatPtr());
}

void Shader::SetVector2Uniform(const char* name, const Vector2& vector)
{
    GLuint loc = glGetUniformLocation(mProgram, name);
    // Send the vector data
    glUniform2fv(loc, 1, vector.GetAsFloatPtr());
}

void Shader::SetFloatUniform(const char* name, float value)
{
    GLuint loc = glGetUniformLocation(mProgram, name);
    // Send the float data
    glUniform1f(loc, value);
}

void Shader::SetIntUniform(const char* name, int value)
{
    GLuint loc = glGetUniformLocation(mProgram, name);
    // Send the float data
    glUniform1i(loc, value);
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