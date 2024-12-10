# コンパイラとオプション
CXX = g++
CXXFLAGS = -Wall -std=c++11

# ソースファイルとオブジェクトファイル
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:%.cpp=%.o)

# コンパイルオプション
INCLUDE = -I../include 
LIBRARY = -lSDL2 -lSDL2main -lSDL2_ttf -lSDL2_mixer -lSDL2_image -lGL -lGLEW -lSOIL -pthread -lGLU
# 出力のターゲット
TARGET = Main

# 全体ビルドターゲット
all: $(TARGET)

# リンクターゲット
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(INCLUDE) $(LIBRARY)

# コンパイル
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# クリーンターゲット
clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean