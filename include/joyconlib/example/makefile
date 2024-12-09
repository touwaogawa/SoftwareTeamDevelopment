#
CC = gcc
ifeq ($(shell uname),Darwin)
CFLAGS = -Wall $(COPTIONS) -I/opt/homebrew/include
LDFLAGS = 
LOADLIBES = -L/opt/homebrew/lib
# LDLIBS = -lm -lSDL2 -lSDL2_ttf -ljoyconlib -lhidapi
LDLIBS = -lm -lSDL2 -lSDL2_ttf -ljoyconlib
endif
ifeq ($(shell uname),Linux)
CFLAGS = -Wall $(COPTIONS)
LDFLAGS = 
LOADLIBES = #-L/usr/local/lib
# LDLIBS = -lm -lSDL2 -lSDL2_image -lSDL2_ttf -Wl,-rpath,/usr/local/lib
LDLIBS = -lm -lSDL2 -lSDL2_ttf -ljoyconlib -lhidapi-hidraw
endif
TARGET = extool
OBJS = $(TARGET).o

release: CPPFLAGS = 
release: COPTIONS = -O3
release: $(TARGET)

debug: CPPFLAGS = 
debug: COPTIONS = -g3 -DDEBUG
debug: LOADLIBES =  -L../Debug -L/opt/homebrew/lib
debug: $(TARGET)

# 暗黙のルールでの動作は以下の通り
# cソースからオブジェクト
#   $(CC) $(CFLAGS) $(CPPFLAGS) -c n.c -o n.o
# オブジェクトから実行ファイル
#   $(CC) $(LDFLAGS) n.o $(LOADLIBES) $(LDLIBS) -o n
#
# $(TARGET): CPPFLAGS = 
# $(TARGET): COPTIONS = -g3
$(TARGET): $(OBJS)
$(OBJS): $(HEADS)

.PHONY: clean
clean:
	@rm -f $(TARGET) $(OBJS) core
