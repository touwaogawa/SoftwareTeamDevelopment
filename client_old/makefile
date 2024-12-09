CXX = g++
CXXFLAGS = -Wall -std=c++11 -I../include -pthread
LDFLAGS = -lSDL2 -lSDL2main -lSDL2_ttf -lSDL2_mixer -lSDL2_image -lGL -lGLEW -lSOIL

OBJDIR = obj

SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:%.cpp=$(OBJDIR)/%.o)

TARGET = Main

all: $(OBJDIR) $(TARGET)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

$(OBJDIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(TARGET)

.PHONY: all clean
