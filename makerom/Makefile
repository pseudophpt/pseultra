#
# pseultra/g\/Makefile
# Boot checksum calculator makefile
# 
# (C) pseudophpt, fraser 2018
#

ifdef SystemRoot
# Windows
TOOLCHAIN := C:\gcc\bin
# FIXPATH = $(subst /,\,$1)
RM = del /Q
else
# Linux
TOOLCHAIN := /usr/bin
# FIXPATH = $1
RM = rm -f
endif

# Native toolchain

# Tools
CC = $(TOOLCHAIN)/gcc
AS = $(TOOLCHAIN)/as
LD = $(TOOLCHAIN)/ld
OBJCOPY = $(TOOLCHAIN)/objcopy

# Include directory
INCLUDE = ../headers

# Tool flags
CC_FLAGS = -I$(INCLUDE) # Includes

AS_FLAGS = -I$(INCLUDE) # Includes

LD_FLAGS = -lc 

OBJCOPY_FLAGS = 

# Files
APP = makerom 

APP_SRC = elf.c makerom.c

all: $(APP) 

$(APP): $(APP_SRC)
	$(CC) $(CC_FLAGS) -o $@ $^

#
# Clean project target.
#
.PHONY: clean
clean:
	@echo "Cleaning makerom..."
	@$(RM) makerom makerom.exe
