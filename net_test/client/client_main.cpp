#include "client_network.h"
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <termios.h>
#include <stdio.h>

// キー入力を非同期に取得する関数
int getKeyPress() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);  // 入力を即時に処理する
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

int main(int argc, char* argv[]) {
    int client_id = 0;  // デフォルトのID
    int port = 55583;
    // 引数でIDを決める場合の処理
    if (argc > 1) {
        client_id = std::atoi(argv[1]);
    }

    Network network;  // Networkクラスのインスタンスを作成

    // サーバーへ接続
    if (!network.Connect(port, client_id)) {
        std::cout << "接続できませんでした" << std::endl;
        return 0;
    }

    std::cout << "接続しました。Tキーでチャットモードに移行。" << std::endl;

    bool chatMode = false;
    std::string message;

    // クライアント操作
    while (true) {
        int key = getKeyPress();  // キー入力を取得

        if (key == 27) {  // ESCキーのASCIIコードは27
            std::cout << "接続を切断します。" << std::endl;
            break;
        }

        if (key == 't' || key == 'T') {  // Tキーでチャットモードに移行
            chatMode = true;
            std::cout << "チャットモードに入りました。メッセージを入力してください:" << std::endl;
        }

        if (chatMode) {
            std::getline(std::cin, message);  // ユーザーからメッセージを取得
            if (message.empty()) continue;

            // メッセージをサーバーに送信
            network.SendData<std::string>(message);  // インスタンスメソッドとして呼び出し
            std::cout << "メッセージ送信: " << message << std::endl;

            // 受信したメッセージを表示（自分以外のクライアントからのメッセージ）
            std::string receivedMessage = network.RecvData<std::string>();  // インスタンスメソッドとして呼び出し
            std::cout << "サーバーから受信: " << receivedMessage << std::endl;
        }
    }

    network.ShutDown();  // 接続終了
    return 0;
}
