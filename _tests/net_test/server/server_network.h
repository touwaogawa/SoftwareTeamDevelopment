#pragma once
#include < glm / glm.hpp>
#include <vector>

class Network {
public:
    // いつでもリッスンできる状態になる
    static bool SetUpServer();
    // リッスン開始 接続に成功したらtrueを返す
    static bool StartListen(int clientNum);
    // 終了処理
    static void CloseServer();

    // テンプレート関数を使ってデータ送信
    template <typename T>
    static void SendData(const T& data, int client_id);

    // 指定した型を受け取る
    template <typename T>
    static T RecvData(int client_id);

private:
    // 型ごとにデータをバッファにセットする
    template <typename T>
    static void SetData(const T& data, std::vector<char>& dataBlock);

    // バッファを送信
    static void SendDataBlock(const std::vector<char>& dataBlock, int client_id);
};