#pragma once
#include <glm/glm.hpp>
#include <vector>

class Network {
public:
    static Network& GetInstance()
    {
        static Network instance; // ローカル静的変数でインスタンスを保持
        return instance;
    }
    // サーバーに接続したらtrueを返す。
    bool Connect(int port, int clientID);

    // テンプレート関数を使ってデータ送信
    template <typename T>
    void SendData(const T& data);

    template <typename T>
    T RecvData();

    void ShutDown();

private:
    // コンストラクタをプライベートにすることで外部でインスタンス化できないように
    Network() { }

    // コピーコンストラクタと代入演算子を削除して、インスタンスの複製を防ぐ
    Network(const Network&)            = delete;
    Network& operator=(const Network&) = delete;

    // 型ごとにデータをバッファにセットする
    template <typename T>
    void SetData(const T& data, std::vector<char>& dataBlock);

    // バッファを送信
    void SendDataBlock(const std::vector<char>& dataBlock);
};