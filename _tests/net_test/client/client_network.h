#pragma once
#include < glm / glm.hpp>
#include <vector>

class Network {
public:
    // サーバーに接続したらtrueを返す。
    static bool Connect(int port, int clientID);

    // テンプレート関数を使ってデータ送信
    template <typename T>
    static void SendData(const T& data);

    // 指定して型を受け取る
    template <typename T>
    static T RecvData();

    // 終了処理
    static void ShutDown();

private:
    // 型ごとにデータをバッファにセットする
    template <typename T>
    static void SetData(const T& data, std::vector<char>& dataBlock);

    // バッファを送信
    static void SendDataBlock(const std::vector<char>& dataBlock);
};