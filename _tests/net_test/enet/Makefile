# コンパイル設定
CXX = g++
CXXFLAGS = -std=c++11 -Wall -I../../include
LDFLAGS = -L../../lib -lenet

# ソースファイルとオブジェクトファイル
SRCS = server.cpp client.cpp
OBJS = $(SRCS:.cpp=.o)

# 実行ファイルの名前
TARGETS = server client

# デフォルトターゲット
all: $(TARGETS)

# サーバーのビルドルール
server: server.o
	$(CXX) -o $@ $^ $(LDFLAGS)

# クライアントのビルドルール
client: client.o
	$(CXX) -o $@ $^ $(LDFLAGS)

# .cpp → .o に変換するルール
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# クリーンアップルール
clean:
	rm -f $(OBJS) $(TARGETS)

# .PHONY で明示的にターゲットとして指定
.PHONY: all clean
