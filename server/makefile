# コンパイラとオプション
CXX = g++
CXXFLAGS = -Wall -std=c++17 -g

# ディレクトリ設定
SERVER_SRCDIR = src
COMMON_SRCDIR = ../common/src
UTILS_SRCDIR = ../utils/src
SERVER_OBJDIR = obj/server
COMMON_OBJDIR = obj/common
UTILS_OBJDIR = obj/utils
MYINCDIR = -I../include
MYLIBDIR = -L../lib

# ソースファイルとオブジェクトファイル
SERVER_SOURCES = $(shell find $(SERVER_SRCDIR) -name "*.cpp")
COMMON_SOURCES = $(shell find $(COMMON_SRCDIR) -name "*.cpp")
UTILS_SOURCES = $(shell find $(UTILS_SRCDIR) -name "*.cpp")

# オブジェクトファイルのパスをディレクトリごとに設定
SERVER_OBJECTS = $(patsubst $(SERVER_SRCDIR)/%, $(SERVER_OBJDIR)/%, $(SERVER_SOURCES:.cpp=.o))
COMMON_OBJECTS = $(patsubst $(COMMON_SRCDIR)/%, $(COMMON_OBJDIR)/%, $(COMMON_SOURCES:.cpp=.o))
UTILS_OBJECTS = $(patsubst $(UTILS_SRCDIR)/%, $(UTILS_OBJDIR)/%, $(UTILS_SOURCES:.cpp=.o))

# コンパイルオプション
INCLUDE = $(MYINCDIR) -pthread
LIBRARY = $(MYLIBDIR) -Wl,-rpath,'$$ORIGIN/../lib'  -lSDL2 -lSDL2main -lSDL2_ttf -lSDL2_mixer -lSDL2_image -lGL -lGLU -ljoyconlib -lhidapi-hidraw -lm -lFMOD -lGLEW -lenet -lreactphysics3d

# 出力のターゲット
TARGET = main

# 全体ビルドターゲット
all: $(SERVER_OBJDIR) $(COMMON_OBJDIR) $(UTILS_OBJDIR) $(TARGET)

# obj ディレクトリがない場合は作成
$(SERVER_OBJDIR):
	@mkdir -p $(SERVER_OBJDIR)

$(COMMON_OBJDIR):
	@mkdir -p $(COMMON_OBJDIR)

$(UTILS_OBJDIR):
	@mkdir -p $(UTILS_OBJDIR)

# ソースファイルをオブジェクトファイルに変換
# server/src/ のソースファイルを server/obj/server にオブジェクトファイルを作成
$(SERVER_OBJDIR)/%.o: $(SERVER_SRCDIR)/%.cpp
	@mkdir -p $(dir $@)  # obj/server/components のようなサブディレクトリを作成
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

# common/src/ のソースファイルを server/obj/common にオブジェクトファイルを作成
$(COMMON_OBJDIR)/%.o: $(COMMON_SRCDIR)/%.cpp
	@mkdir -p $(dir $@)  # obj/common のサブディレクトリを作成
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

# utils/src/ のソースファイルを server/obj/utils にオブジェクトファイルを作成
$(UTILS_OBJDIR)/%.o: $(UTILS_SRCDIR)/%.cpp
	@mkdir -p $(dir $@)  # obj/utils のサブディレクトリを作成
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

# ターゲットの作成
$(TARGET): $(SERVER_OBJECTS) $(COMMON_OBJECTS) $(UTILS_OBJECTS)
	$(CXX) $(SERVER_OBJECTS) $(COMMON_OBJECTS) $(UTILS_OBJECTS) -o $@ $(LIBRARY)

# クリーンターゲット
clean:
	rm -f $(SERVER_OBJECTS) $(COMMON_OBJECTS) $(UTILS_OBJECTS) $(TARGET)

.PHONY: all clean
