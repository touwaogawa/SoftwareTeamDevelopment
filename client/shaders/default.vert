#version 330 core

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texcoord;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;

void main() {
    FragPos = vec3(vec4(position, 1.0) * model);
    Normal = mat3(transpose(inverse(model))) * normal;
    TexCoord = texcoord;
    // gl_Position = projection * view * vec4(FragPos, 1.0);
    gl_Position =  vec4(position, 1.0) * model * view * projection;

}
