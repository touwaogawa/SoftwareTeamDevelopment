# コンパイラとオプション
CXX = g++
CXXFLAGS = -Wall -std=c++11

# ソースファイルとオブジェクトファイル
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:%.cpp=%.o)

# コンパイルオプション
OPTION = 
#-I../include -lSDL2 -lSDL2main -lSDL2_ttf -lSDL2_mixer -lSDL2_image -lGL -lGLEW -lSOIL -pthread

# 出力のターゲット
TARGET = Main

# 全体ビルドターゲット
all: $(TARGET)

# リンクターゲット
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(OPTION)

# コンパイル
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# クリーンターゲット
clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean