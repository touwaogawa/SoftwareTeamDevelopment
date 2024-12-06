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
    // いつでもリッスンできる状態になる
    bool SetUpServer();
    // リッスン開始 接続に成功したらtrueを返す
    bool StartListen(int clientNum);
    // 終了処理
    void CloseServer();

    // テンプレート関数を使ってデータ送信
    template <typename T>
    void SendData(const T& data, int client_id);

    template <typename T>
    T RecvData(int client_id);

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
    void SendDataBlock(const std::vector<char>& dataBlock, int client_id);
};