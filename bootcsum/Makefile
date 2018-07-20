#
# pseultra/bootcsum/Makefile
# Boot checksum calculator makefile
# 
# (C) pseudophpt 2018
#

# Native toolchain
TOOLCHAIN := /usr/bin

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

LD_FLAGS = 

OBJCOPY_FLAGS = 

# Files
APP = bootcsum

APP_SRC = bootcsum.c

all: $(APP)

$(APP): $(APP_SRC)
	$(CC) $(CC_FLAGS) -o $@ $<
