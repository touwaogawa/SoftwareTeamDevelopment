#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;
in vec4 FragPosLightSpace;

uniform sampler2D shadowMap;
uniform vec3 lightPos;
uniform vec3 viewPos;

uniform vec3 diffuseLightColor;
uniform vec3 ambientLightColor;

// アンビエントライトの強度
uniform float ambientStrength;

// テクスチャを読み込むサンプラー
uniform sampler2D texture1;

// 影の計算関数
float ShadowCalculation(vec4 fragPosLightSpace)
{
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w; // 正規化
    projCoords = projCoords * 0.5 + 0.5; // [-1,1] -> [0,1]

    // 深度テクスチャから取得
    float closestDepth = texture(shadowMap, projCoords.xy).r;
    float currentDepth = projCoords.z;

    // バイアスでアクネ防止
    float bias = 0.005;
    float shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;

    return shadow;
}

void main()
{
    // アンビエントライト
    vec3 ambient = ambientStrength * ambientLightColor;

    // 拡散光
    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * diffuseLightColor;

    // スペキュラ (鏡面反射)
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * diffuseLightColor;

    // テクスチャから色を取得
    vec3 texColor = texture(texture1, TexCoord).rgb;

    // 影の計算
    float shadow = ShadowCalculation(FragPosLightSpace);

    // 光源計算 (影は拡散光にのみ影響)
    vec3 lighting = ambient + (1.0 - shadow) * (diffuse + specular);
    lighting *= texColor;

    FragColor = vec4(lighting, 1.0);
}

