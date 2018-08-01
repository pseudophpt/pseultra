PREFIX = /opt/pseultra

SRCDIR = src
OBJDIR = obj
LIBDIR = lib
DOCDIR = doc
INCDIR = include
BINDIR = bin

INCLUDES = include ../../include
INCLUDE_FLAGS = $(foreach includedir, $(INCLUDES), -I$(includedir))

CFLAGS = $(INCLUDE_FLAGS)

SRC_FILES_C = $(shell find $(SRCDIR) -name '*.c') 
SRC_FILES_S = $(shell find $(SRCDIR) -name '*.s') 

SRC_FILES = $(SRC_FILES_C) $(SRC_FILES_S)

OBJ_FILES = $(patsubst src/%.c, obj/%.o, $(SRC_FILES_C)) $(patsubst src/%.s, obj/%.o, $(SRC_FILES_S))

APP := bin/bootcsumr

.PHONY: all clean install

all: $(APP)

$(APP): $(OBJ_FILES)
	$(CC) $(CFLAGS) \
	-o $@ \
	$^

$(OBJ_FILES): $(SRC_FILES)
# Compile c files 
	$(foreach src, $(SRC_FILES_C), \
		$(CC) $(CFLAGS) \
		-c \
		-o $(patsubst src/%.c, obj/%.o, $(src)) \
		$(src); \
	)
# Compile asm files 
	$(foreach src, $(SRC_FILES_S), \
		$(CC) $(CFLAGS) \
		-c \
		-o $(patsubst src/%.s, obj/%.o, $(src)) \
		$(src); \
	)

install:
	cp -r $(BINDIR)/ $(PREFIX)
	cp -r $(LIBDIR)/ $(PREFIX)
	cp -r $(INCDIR)/ $(PREFIX)

clean:
	rm $(OBJ_FILES)
