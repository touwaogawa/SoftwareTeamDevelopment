# コンパイラとオプション
CXX = g++
CXXFLAGS = -Wall -std=c++11

# ディレクトリ設定
SRCDIR = src
OBJDIR = obj

# ソースファイルとオブジェクトファイル
SOURCES = $(wildcard $(SRCDIR)/**/*.cpp)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# コンパイルオプション
OPTION = -I../include -lSDL2 -lSDL2main -lSDL2_ttf -lSDL2_mixer -lSDL2_image -lGL -lGLEW -lSOIL -pthread

# 出力のターゲット
TARGET = main

# 全体ビルドターゲット
all: $(TARGET)

# リンクターゲット
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(OPTION)

# コンパイル
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# クリーンターゲット
clean:
	rm -rf $(OBJDIR) $(TARGET)

.PHONY: all clean
