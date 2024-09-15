# 最低限のCMakeバージョンを設定
cmake_minimum_required(VERSION 3.10)

# プロジェクトの設定
project(MyProject)

# C++17 標準を指定（必要に応じて）
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# ターゲットの追加
add_executable(client ./src/client/client.cpp)
add_executable(server ./src/server/server.cpp)

# pthread ライブラリのリンク（UNIX系システム用）
find_package(Threads REQUIRED)
target_link_libraries(client PRIVATE Threads::Threads)
target_link_libraries(server PRIVATE Threads::Threads)
