#version 330 core

uniform mat4 model;       // モデル行列
uniform mat4 view;        // ビュー行列
uniform mat4 projection;  // プロジェクション行列
uniform vec3 viewPos;

layout(location = 0) in vec3 position;
// layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texcoord;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;

// void main() {
//     // ビュー行列から回転成分（上3x3部分）を取得
//     mat3 viewRotation = mat3(view);

//     // ビルボード用モデル行列の作成
//     mat4 billboardModel = mat4(1.0);          // 単位行列で初期化
//     billboardModel[0].xyz = viewRotation[0];  // X軸の回転
//     billboardModel[1].xyz = viewRotation[1];  // Y軸の回転
//     billboardModel[2].xyz = viewRotation[2];  // Z軸の回転
//     billboardModel[3] = model[3];             // 平行移動（モデルの位置）

//     // フラグメント用の値を計算
//     FragPos = vec3(billboardModel * vec4(position, 1.0));
//     Normal = mat3(transpose(inverse(billboardModel))) * normal;
//     TexCoord = texcoord;

//     // 最終的な変換
//     gl_Position = projection * view * vec4(FragPos, 1.0);
// }

void main()
{
    // ビルボードの回転を計算
    // ビルボードはカメラの向きを向くように回転させる
    mat4 rotationMatrix = mat4(1.0);
    
    // ビルボードの回転を計算（カメラの位置を基準に）
    vec3 billboardForward = normalize(viewPos - vec3(model[3]));  // モデルの位置からカメラに向かうベクトル
    vec3 billboardUp = vec3(0.0, 1.0, 0.0); // 通常、ビルボードはY軸が上になるように回転

    // 正面と上方向ベクトルを計算
    vec3 billboardRight = normalize(cross(billboardUp, billboardForward)); // 右方向ベクトル
    billboardUp = cross(billboardForward, billboardRight);  // 上方向ベクトルの再計算

    // 回転行列を作成
    rotationMatrix[0] = vec4(billboardRight, 0.0);
    rotationMatrix[1] = vec4(billboardUp, 0.0);
    rotationMatrix[2] = vec4(-billboardForward, 0.0);  // 前方向は反転させる
    rotationMatrix[3] = vec4(0.0, 0.0, 0.0, 1.0);

    // モデル行列に回転行列を適用
    mat4 finalModel = rotationMatrix * model;

    // 最終的な位置の計算
    gl_Position = vec4(position, 1.0) * finalModel * view * projection;
    
    // テクスチャ座標はそのまま渡す
    TexCoord = texcoord;
}