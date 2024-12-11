#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>

class Shader {
public:
    Shader();

    bool Load(const std::string& vertexPath, const std::string& fragmentPath);
    void Use();
    GLuint GetProgram() const;

private:
    bool checkCompileErrors(GLuint shader, GLenum shaderType);
    bool CompileShader(const std::string& fileName,
        GLenum shaderType,
        GLuint& outShader);
    GLuint mProgram;
};

#endif
