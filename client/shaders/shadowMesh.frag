#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;
in vec4 FragPosLightSpace;

uniform sampler2D shadowMap;
uniform vec3 lightPos;
uniform vec3 viewPos;

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
    vec3 color = vec3(0.3, 0.3, 0.3); // ベースカラー
    vec3 lightColor = vec3(1.0, 1.0, 1.0);

    // 拡散光
    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // 影の計算
    float shadow = ShadowCalculation(FragPosLightSpace);
    vec3 lighting = (1.0 - shadow) * diffuse + color;

    FragColor = vec4(lighting, 1.0);
}
