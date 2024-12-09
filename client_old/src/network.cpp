#include "network.h"

// バッファにデータをセット
template <typename T>
void Network::SetData(const T& data, std::vector<char>& dataBlock)
{
    const char* dataPtr = reinterpret_cast<const char*>(&data);
    dataBlock.insert(dataBlock.end(), dataPtr, dataPtr + sizeof(T));
}

// 特化化（行列用）
template <>
void Network::SetData(const glm::mat3& data, std::vector<char>& dataBlock)
{
    for (int i = 0; i < 9; ++i) {
        SetData(data[i], dataBlock);
    }
}

template <>
void Network::SetData(const glm::mat4& data, std::vector<char>& dataBlock)
{
    for (int i = 0; i < 16; ++i) {
        SetData(data[i], dataBlock);
    }
}

// SendDataを呼び出す関数（データ型に基づいてSendDataBlockを呼び出し）
template <typename T>
void Network::SendData(const T& data)
{
    std::vector<char> dataBlock;
    SetData(data, dataBlock);
    SendDataBlock(dataBlock);
}

// 受信データ（バッファからデータを取得）
template <typename T>
T Network::RecvData()
{
    T data;
    char buffer[sizeof(T)];
    // recv関数（仮の実装）でデータを受信
    // recv(socket, buffer, sizeof(T), 0);
    std::memcpy(&data, buffer, sizeof(T)); // バッファからデータを読み取る
    return data;
}

// SendDataBlockで実際にデータを送信する
void Network::SendDataBlock(const std::vector<char>& dataBlock)
{
    // 実際の送信処理
}