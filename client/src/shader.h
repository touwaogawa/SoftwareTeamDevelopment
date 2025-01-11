#pragma once
#include "../../utils/src/math.h"
#include <GL/glew.h>
#include <string>

class Shader {
public:
    Shader();

    bool Load(const std::string& vertexPath, const std::string& fragmentPath);
    void Use();
    GLuint GetProgram() const;

    // Sets a Matrix uniform
    void SetMatrixUniform(const char* name, const Matrix4& matrix);
    // Sets an array of matrix uniforms
    void SetMatrixUniforms(const char* name, Matrix4* matrices, unsigned count);
    // Sets a Vector3 uniform
    void SetVector3Uniform(const char* name, const Vector3& vector);
    void SetVector2Uniform(const char* name, const Vector2& vector);

    // Sets a float uniform
    void SetFloatUniform(const char* name, float value);
    // Sets an integer uniform
    void SetIntUniform(const char* name, int value);

private:
    bool checkCompileErrors(GLuint shader, GLenum shaderType);
    bool CompileShader(const std::string& fileName,
        GLenum shaderType,
        GLuint& outShader);
    GLuint mProgram;
};
