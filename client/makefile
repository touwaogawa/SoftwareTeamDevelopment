# コンパイラとオプション
CXX = g++
CXXFLAGS = -Wall -std=c++11

# ディレクトリ設定
SRCDIR = src
OBJDIR = obj

# ソースファイルとオブジェクトファイル
SOURCES = $(SRCDIR)/client_main.cpp $(SRCDIR)/client_game.cpp $(SRCDIR)/client_renderer.cpp
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# コンパイルオプション
OPTION = -lSDL2 -lSDL2_image

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
