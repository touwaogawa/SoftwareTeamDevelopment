# コンパイラとオプション
CXX = g++
CXXFLAGS = -Wall -std=c++14

# ディレクトリ設定
SRCDIR = src
OBJDIR = obj
MYINCDIR = -I../include
MYLIBDIR = -L../lib

# ソースファイルとオブジェクトファイル
SOURCES = $(shell find $(SRCDIR) -name "*.cpp")
SOURCES_NOTDIR = $(notdir $(SOURCES))
SOURCES_DIRS = $(dir $(SOURCES))  # 各ソースファイルのディレクトリ部分
OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))  # ディレクトリ構造を保ったままオブジェクトファイルを作成

# コンパイルオプション
INCLUDE = $(MYINCDIR) -pthread
LIBRARY = $(MYLIBDIR) -lSDL2 -lSDL2main -lSDL2_ttf -lSDL2_mixer -lSDL2_image -lGL -lGLEW -lSOIL -lGLU -ljoyconlib -lhidapi-hidraw -lm

# 出力のターゲット
TARGET = main

# 全体ビルドターゲット
all: $(OBJDIR) $(TARGET)

# LD_LIBRARY_PATH=../lib:$$LD_LIBRARY_PATH ./$(TARGET)

# obj ディレクトリがない場合は作成
$(OBJDIR):
	@mkdir -p $(OBJDIR)

# ターゲットの作成
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LIBRARY)

# ソースファイルをオブジェクトファイルに変換
# すべての .o ファイルを obj フォルダ内の同じ層に作成する
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)  # obj/ディレクトリ内にサブディレクトリを作成
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

# クリーンターゲット
clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean

show:
	@echo "Sources: $(SOURCES)"
	@echo "Objects: $(OBJECTS)"
