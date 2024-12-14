# コンパイラとオプション
CXX = g++
CXXFLAGS = -Wall -std=c++14

# ディレクトリ設定
SRCDIR = src
OBJDIR = obj

# ソースファイルとオブジェクトファイル
SOURCES = $(wildcard $(SRCDIR)/**/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o,  $(notdir $(SOURCES)))

# コンパイルオプション
INCLUDE = -I../include -pthread
LIBRARY = -lSDL2 -lSDL2main -lSDL2_ttf -lSDL2_mixer -lSDL2_image -lGL -lGLEW -lSOIL -lGLU -ljoyconlib -lhidapi-hidraw -lm

# 出力のターゲット
TARGET = main

# 全体ビルドターゲット
all: $(OBJDIR) $(TARGET)

# obj ディレクトリがない場合は作成
$(OBJDIR):
	@mkdir -p $(OBJDIR)

# ターゲットの作成
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LIBRARY)

# ソースファイルをオブジェクトファイルに変換
# すべての .o ファイルを obj フォルダ内の同じ層に作成する
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $(OBJDIR)/$(notdir $@)

# クリーンターゲット
clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean
