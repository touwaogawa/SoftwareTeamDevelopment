#pragma once
#include <glm/glm.hpp>
#include <vector>

class Network {
public:
    // テンプレート関数を使ってデータ送信
    template <typename T>
    void SendData(const T& data);

    template <typename T>
    T RecvData();

private:
    // 型ごとにデータをバッファにセットする
    template <typename T>
    void SetData(const T& data, std::vector<char>& dataBlock);

    // バッファを送信
    void SendDataBlock(const std::vector<char>& dataBlock);
};