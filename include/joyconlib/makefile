#
LIBNAME = libjoyconlib
SO_VER = 0
DY_VER = 0.1
REAL_VER = 0.1.0
INST_DIR = /usr/local

SONAME_NO_VER	= $(LIBNAME).so
SONAME		= $(SONAME_NO_VER).$(SO_VER)
REAL_NAME	= $(SONAME_NO_VER).$(REAL_VER)

DYNAME_NO_VER = $(LIBNAME).dylib
DYNAME = $(LIBNAME).$(SO_VER).dylib
REAL_DYNAME = $(LIBNAME).$(REAL_VER).dylib

DIR_Debug = ./Debug/
SO_Debug = $(DIR_Debug)$(REAL_NAME)
DY_Debug = $(DIR_Debug)$(REAL_DYNAME)

OBJS = joyconlib.o joyconlib_rumble.o joyconlib_mcu.o
HEADS = joyconlib.h joyconlib_types.h ir_sensor.h

OBJS_SO_Debug	= $(addprefix $(DIR_Debug),$(OBJS))

CC = gcc
ifeq ($(shell uname),Darwin)
CFLAGS = -Wall $(COPTIONS) -I/opt/homebrew/include
LDFLAGS = 
LOADLIBES = -L/opt/homebrew/lib
LDLIBS =
INSTALL_REAL = $(REAL_DYNAME)
INSTALL_SONAME = $(DYNAME)
INSTALL_NO_VER = $(DYNAME_NO_VER)
endif
ifeq ($(shell uname),Linux)
CFLAGS = -Wall $(COPTIONS)
LDFLAGS = 
LOADLIBES = #-L/usr/local/lib
LDLIBS =
INSTALL_REAL = $(REAL_NAME)
INSTALL_SONAME = $(SONAME)
INSTALL_NO_VER = $(SONAME_NO_VER)
endif

release: CPPFLAGS = 
release: COPTIONS = -O3
ifeq ($(shell uname),Darwin)
release: $(REAL_DYNAME)
endif
ifeq ($(shell uname),Linux)
release: $(REAL_NAME)
endif

$(REAL_DYNAME): $(OBJS)
	$(CC) -dynamiclib -install_name $(INST_DIR)/lib/$(DYNAME) -compatibility_version $(DY_VER) -current_version $(REAL_VER) $(LOADLIBES) -lhidapi -o $(REAL_DYNAME) $(OBJS)

$(REAL_NAME): $(OBJS)
	$(CC) -shared -Wl,-soname,$(SONAME) -o $(REAL_NAME) $(OBJS)
	strip $(REAL_NAME)

$(OBJS): $(HEADS)

debug: CPPFLAGS = 
debug: COPTIONS = -g3 -DDEBUG
ifeq ($(shell uname),Darwin)
debug: $(DY_Debug)
endif
ifeq ($(shell uname),Linux)
debug: $(SO_Debug)
endif

$(DY_Debug): $(OBJS_SO_Debug)
	$(CC) -dynamiclib -install_name $(DYNAME) -compatibility_version $(DY_VER) -current_version $(REAL_VER) $(LOADLIBES) -lhidapi -o $(DY_Debug) $(OBJS_SO_Debug)
	ln -sfr $(DIR_Debug)$(INSTALL_REAL) $(DIR_Debug)$(INSTALL_SONAME)
	ln -sfr $(DIR_Debug)$(INSTALL_REAL) $(DIR_Debug)$(INSTALL_NO_VER)

$(SO_Debug): $(OBJS_SO_Debug)
	gcc -shared -Wl,-soname,$(SONAME) -o $(SO_Debug) $(OBJS_SO_Debug)
	ln -sfr $(DIR_Debug)$(INSTALL_REAL) $(DIR_Debug)$(INSTALL_SONAME)
	ln -sfr $(DIR_Debug)$(INSTALL_REAL) $(DIR_Debug)$(INSTALL_NO_VER)

$(OBJS_SO_Debug): $(DIR_Debug)%.o: %.c $(HEADS)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

install:
	install -d $(INST_DIR)/lib $(INST_DIR)/include $(INST_DIR)/share/doc/joyconlib/example
	install -m 644 joyconlib.h $(INST_DIR)/include
	install $(INSTALL_REAL) $(INST_DIR)/lib
	ln -sfr $(INST_DIR)/lib/$(INSTALL_REAL) $(INST_DIR)/lib/$(INSTALL_SONAME)
	ln -sfr $(INST_DIR)/lib/$(INSTALL_REAL) $(INST_DIR)/lib/$(INSTALL_NO_VER)
	install -m 644 example/extool.c example/makefile $(INST_DIR)/share/doc/joyconlib/example
#	install -m 644 [docfile] $(INST_DIR)/share/doc/joyconlib

.PHONY: clean
clean:
	@rm -f $(REAL_NAME) $(REAL_DYNAME) $(OBJS) $(OBJS_SO_Debug) $(SO_Debug) $(DY_Debug)
