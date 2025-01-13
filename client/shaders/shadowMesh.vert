#version 330 core
uniform mat4 model;
uniform mat4 viewProjection;
uniform mat4 lightSpaceMatrix;

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texcoord;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;
out vec4 FragPosLightSpace;


void main()
{
    FragPos = vec3(vec4(position, 1.0) * model);
    Normal = mat3(transpose(inverse(model))) * normal;
    TexCoord = texcoord;
    FragPosLightSpace = vec4(FragPos, 1.0) * lightSpaceMatrix;

    gl_Position =  vec4(FragPos, 1.0) * viewProjection;
}
