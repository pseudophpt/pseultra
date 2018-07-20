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
CC_FLAGS = -O3 -I$(INCLUDE) # Includes

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
