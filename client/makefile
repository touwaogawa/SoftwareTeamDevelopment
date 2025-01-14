# コンパイラとオプション
CXX = g++
CXXFLAGS = -Wall -std=c++17 -g

# ディレクトリ設定
CLIENT_SRCDIR = src
COMMON_SRCDIR = ../common/src
UTILS_SRCDIR = ../utils/src
CLIENT_OBJDIR = obj/client
COMMON_OBJDIR = obj/common
UTILS_OBJDIR = obj/utils
MYINCDIR = -I../include
MYLIBDIR = -L../lib

# ソースファイルとオブジェクトファイル
CLIENT_SOURCES = $(shell find $(CLIENT_SRCDIR) -name "*.cpp")
COMMON_SOURCES = $(shell find $(COMMON_SRCDIR) -name "*.cpp")
UTILS_SOURCES = $(shell find $(UTILS_SRCDIR) -name "*.cpp")

# オブジェクトファイルのパスをディレクトリごとに設定
CLIENT_OBJECTS = $(patsubst $(CLIENT_SRCDIR)/%, $(CLIENT_OBJDIR)/%, $(CLIENT_SOURCES:.cpp=.o))
COMMON_OBJECTS = $(patsubst $(COMMON_SRCDIR)/%, $(COMMON_OBJDIR)/%, $(COMMON_SOURCES:.cpp=.o))
UTILS_OBJECTS = $(patsubst $(UTILS_SRCDIR)/%, $(UTILS_OBJDIR)/%, $(UTILS_SOURCES:.cpp=.o))

# コンパイルオプション
INCLUDE = $(MYINCDIR)
LIBRARY = $(MYLIBDIR) -lSDL2 -lSDL2_mixer -lSDL2_image -lGL -lGLU -ljoyconlib -lhidapi-hidraw -lm -lGLEW -lenet -lreactphysics3d -ltinyobjloader -lpng -lharfbuzz -lz -pthread 

# -lFLAC

# -Wl,-rpath,'$$ORIGIN/../lib' -lSDL2main -lSDL2_ttf
# 出力のターゲット
TARGET = main

# 全体ビルドターゲット
all: $(CLIENT_OBJDIR) $(COMMON_OBJDIR) $(UTILS_OBJDIR) $(TARGET)

# obj ディレクトリがない場合は作成
$(CLIENT_OBJDIR):
	@mkdir -p $(CLIENT_OBJDIR)

$(COMMON_OBJDIR):
	@mkdir -p $(COMMON_OBJDIR)

$(UTILS_OBJDIR):
	@mkdir -p $(UTILS_OBJDIR)

# ソースファイルをオブジェクトファイルに変換
# client/src/ のソースファイルを client/obj/client にオブジェクトファイルを作成
$(CLIENT_OBJDIR)/%.o: $(CLIENT_SRCDIR)/%.cpp
	@mkdir -p $(dir $@)  # obj/client/components のようなサブディレクトリを作成
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

# common/src/ のソースファイルを client/obj/common にオブジェクトファイルを作成
$(COMMON_OBJDIR)/%.o: $(COMMON_SRCDIR)/%.cpp
	@mkdir -p $(dir $@)  # obj/common のサブディレクトリを作成
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

# utils/src/ のソースファイルを client/obj/utils にオブジェクトファイルを作成
$(UTILS_OBJDIR)/%.o: $(UTILS_SRCDIR)/%.cpp
	@mkdir -p $(dir $@)  # obj/utils のサブディレクトリを作成
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

# ターゲットの作成
$(TARGET): $(CLIENT_OBJECTS) $(COMMON_OBJECTS) $(UTILS_OBJECTS)
	$(CXX) $(CLIENT_OBJECTS) $(COMMON_OBJECTS) $(UTILS_OBJECTS) -o $@ $(LIBRARY)

# クリーンターゲット
clean:
	rm -f $(CLIENT_OBJECTS) $(COMMON_OBJECTS) $(UTILS_OBJECTS) $(TARGET)

.PHONY: all clean
