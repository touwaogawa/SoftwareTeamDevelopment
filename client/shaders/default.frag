#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

// ライト関連の uniform 変数
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 diffuseLightColor;
uniform vec3 ambientLightColor;
uniform vec3 objectColor;

// アンビエントライトの強度
uniform float ambientStrength;

//テクスチャを読み込むサンプラー
uniform sampler2D texture1;

void main() {
    // アンビエントライト
    vec3 ambient = ambientStrength * ambientLightColor;

    // 拡散光 (ディフューズ)
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * diffuseLightColor;

    // スペキュラ (鏡面反射)
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * diffuseLightColor;

    // テクスチャから色を取得
    vec3 texColor = texture(texture1, TexCoord).rgb;

    // 最終結果
    vec3 result = (ambient + diffuse + specular) * texColor;
    FragColor = vec4(result, 1.0);
}
