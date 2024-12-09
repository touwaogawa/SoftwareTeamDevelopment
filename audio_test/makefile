# コンパイラとオプション
CXX = g++
CXXFLAGS = -Wall -std=c++17 -g  # 最新のC++標準とデバッグオプション

# ソースファイルとオブジェクトファイル
# SOURCES = $(wildcard *.cpp)
SOURCES = main.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# コンパイルオプション
INCLUDES = -I../include
LIBS = -lfmod -lSDL2

# 出力のターゲット
TARGET = main

# 全体ビルドターゲット
all: $(TARGET)

# リンクターゲット
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(INCLUDES) $(LIBS)

# コンパイル
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# クリーンターゲット
clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean
