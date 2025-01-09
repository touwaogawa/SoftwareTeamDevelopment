#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;
out vec4 FragPosLightSpace;

uniform mat4 model;
// uniform mat4 view;
// uniform mat4 projection;
uniform mat4 viewProjection;
uniform mat4 lightSpaceMatrix;

void main()
{
    FragPos = vec3(vec4(aPos, 1.0) * model);
    Normal = mat3(transpose(inverse(model))) * aNormal;
    TexCoords = aTexCoord;
    FragPosLightSpace = vec4(FragPos, 1.0) * lightSpaceMatrix;

    gl_Position =  vec4(FragPos, 1.0) * viewProjection;
}
