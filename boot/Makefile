#
# pseultra/boot/Makefile
# Bootcode makefile
# 
# (C) pseudophpt 2018
#

# MIPS Toolchain
TOOLCHAIN := /opt/mips/mips64/bin

# Tools
CC = $(TOOLCHAIN)/gcc
AS = $(TOOLCHAIN)/as
LD = $(TOOLCHAIN)/ld
OBJCOPY = $(TOOLCHAIN)/objcopy

# Include directory
INCLUDE = ../headers

# Tool flags
CC_FLAGS = -I$(INCLUDE) # Includes 

AS_FLAGS = -EB -I$(INCLUDE) # Includes # Big endian

LD_FLAGS = 

OBJCOPY_FLAGS = 

# Files
BOOTFILE = boot

BOOTELF = boot.elf

BOOTOBJECT = boot.o

BOOTSRC = boot.s

all: $(BOOTFILE)

clean:
	rm $(BOOTELF)
	rm $(BOOTOBJECT)

$(BOOTFILE): $(BOOTELF)
	$(OBJCOPY) $(OBJCOPY_FLAGS) -O binary $< $@

$(BOOTELF): $(BOOTOBJECT)
	$(LD) $(LD_FLAGS) -T link.ld

$(BOOTOBJECT): $(BOOTSRC)
	$(AS) $(AS_FLAGS) -o $@ $<
