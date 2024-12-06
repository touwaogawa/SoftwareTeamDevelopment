#pragma once

class Input {
public:
    static Input& GetInstance()
    {
        static Input instance; // ローカル静的変数でインスタンスを保持
        return instance;
    }

private:
    // コンストラクタをプライベートにすることで外部でインスタンス化できないように
    Input() { }

    // コピーコンストラクタと代入演算子を削除して、インスタンスの複製を防ぐ
    Input(const Input&)            = delete;
    Input& operator=(const Input&) = delete;
};