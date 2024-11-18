# コンパイラとオプション
CXX = g++
CXXFLAGS = -Wall -std=c++11

# ディレクトリ設定
SRCDIR = src
OBJDIR = obj

# ソースファイルとオブジェクトファイル
SOURCES = $(SRCDIR)/client_main.cpp $(SRCDIR)/client_game_system/game.cpp $(SRCDIR)/client_renderer.cpp
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# 出力のターゲット
TARGET = $(OBJDIR)/main

# 全体ビルドターゲット
all: $(TARGET)

# リンクターゲット
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) -lSDL2

# コンパイル
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# クリーンターゲット
clean:
	rm -rf $(OBJDIR) $(TARGET)

.PHONY: all clean
