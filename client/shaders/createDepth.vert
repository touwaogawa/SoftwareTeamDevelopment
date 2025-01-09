#version 330 core
layout (location = 0) in vec3 position;

uniform mat4 lightSpaceMatrix;
uniform mat4 model;

out vec3 FragPos;

void main()
{
    FragPos = vec3(vec4(position, 1.0) * model);
    gl_Position = vec4(FragPos, 1.0) * lightSpaceMatrix;
}
