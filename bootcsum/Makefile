#
# pseultra/bootcsum/Makefile
# Boot checksum calculator makefile
# 
# (C) pseudophpt 2018
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
CC_FLAGS = -Ofast -I$(INCLUDE) # Includes

AS_FLAGS = -I$(INCLUDE) # Includes

LD_FLAGS = 

OBJCOPY_FLAGS = 

# Files
APP = bootcsum
APPR = bootcsumr

APP_SRC = bootcsum.c
APPR_SRC  = bootcsumr.c

all: $(APP) $(APPR)

$(APP): $(APP_SRC)
	$(CC) $(CC_FLAGS) -o $@ $<

$(APPR): $(APPR_SRC)
	$(CC) $(CC_FLAGS) -o $@ $<

#
# Clean project target.
#
.PHONY: clean
clean:
	@echo "Cleaning bootcsum..."
	@$(RM) bootcsum bootcsumr bootcsum.exe bootcsumr.exe