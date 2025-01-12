#version 330 core

// Tex coord input from vertex shader
in vec2 TexCoord;

// This corresponds to the output color to the color buffer
out vec4 FragColor;

// This is used for the texture sampling
uniform sampler2D uTexture;

// Flag to determine whether to use custom color
uniform bool useCustomColor; // テキストを使うかどうかを制御するフラグ

// Custom color to apply when UseColur is true
uniform vec3 customColor; // カスタムカラー

const float epsilon = 1e-6;

void main()
{
    vec4 texSample = texture(uTexture, TexCoord);
    if (useCustomColor) {
        bool isWhite = (abs(texSample.r - 1.0) < epsilon &&
                        abs(texSample.g - 1.0) < epsilon &&
                        abs(texSample.b - 1.0) < epsilon);
        if(isWhite){
            FragColor = vec4(customColor, texSample.a);
        }else {
            FragColor = texSample;
        }
    } else {
        FragColor = texSample;
        // カラーを使わない場合は、テクスチャの色をそのまま使用
    }
}
