# Variables
CXX = g++
CXXFLAGS = -Iexternal/SDL/include -Iexternal/GLEW/include -Iexternal/SOIL/include -Iexternal/rapidjson/include
LDFLAGS = -Lexternal/SDL/lib -Lexternal/GLEW/lib -Lexternal/SOIL/lib
LIBS = -lSDL2 -lSDL2_ttf -lSDL2_mixer -lSDL2_image -lGLEW -lSOIL -lGL
OBJ_DIR = obj
BIN_DIR = bin
TARGET = $(BIN_DIR)/Game

# Source files
SRCS = Actor.cpp CameraActor.cpp CircleComponent.cpp \
       Component.cpp Game.cpp Main.cpp Math.cpp \
       Mesh.cpp MeshComponent.cpp MoveComponent.cpp \
       PlaneActor.cpp Renderer.cpp Shader.cpp \
       SpriteComponent.cpp Texture.cpp VertexArray.cpp

# Object files
OBJS = $(SRCS:%.cpp=$(OBJ_DIR)/%.o)

# Rules
all: $(TARGET)

$(TARGET): $(OBJS)
	mkdir -p $(BIN_DIR)
	$(CXX) -o $(TARGET) $(OBJS) $(LDFLAGS) $(LIBS)

# Compile each .cpp file to an object file in the obj directory
$(OBJ_DIR)/%.o: %.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean
