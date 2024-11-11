# Makefile for building the project

# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++11
LDFLAGS = -lm -lSDL2

# Directories
SRCDIR = src
OBJDIR = obj
OBJGAME = $(OBJDIR)/game_system

# Source files
SOURCES = $(SRCDIR)/client_main.cpp $(SRCDIR)/game_system/client_game_system.cpp
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# Output binary
TARGET = main

# Targets
all: $(TARGET)

# Linking the final executable
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

# Compile each source file into object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)/game_system  # Ensure the game_system directory exists
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up object files and the target
clean:
	rm -rf $(OBJDIR) $(TARGET)

.PHONY: all clean
