#version 330 core

uniform mat4 view;  
uniform mat4 projection;  
uniform mat4 model;
uniform vec3 scale;
uniform bool isSpherical;

layout(location = 0) in vec3 position;  // 頂点位置
layout(location = 2) in vec2 texcoord;  // テクスチャ座標

out vec2 TexCoord;  // フラグメントシェーダに渡すテクスチャ座標

void main()
{
    mat4 modelView = model * view;
    // 列ベクトルを取得
    vec3 col1 = vec3(model[0][0], model[1][0], model[2][0]); // X軸
    vec3 col2 = vec3(model[0][1], model[1][1], model[2][1]); // Y軸
    vec3 col3 = vec3(model[0][2], model[1][2], model[2][2]); // Z軸
    
    // First colunm.
    modelView[0][0] = length(col1); 
    modelView[1][0] = 0.0; 
    modelView[2][0] = 0.0; 

    // Second colunm.
    if(isSpherical){
        modelView[0][1] = 0.0; 
        modelView[1][1] = length(col2); 
        modelView[2][1] = 0.0; 
    }

    // Thrid colunm.
    modelView[0][2] = 0.0; 
    modelView[1][2] = 0.0; 
    modelView[2][2] = length(col3); 

    vec4 P = vec4(position, 1.0) * modelView;

    gl_Position = P * projection;

    TexCoord = texcoord;
}