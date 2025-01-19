#version 330 core


in vec2 TexCoord;

uniform sampler2D uTexture;

out vec4 FragColor;

void main()
{
     vec4 texColor = texture(uTexture, TexCoord);

    // // アルファ値が0.1未満ならそのピクセルを破棄
    if (texColor.a < 0.1)
        discard;

    FragColor = texColor;
}