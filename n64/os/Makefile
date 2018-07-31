#
# pseultra/os/Makefile
# OS makefile
# 
# (C) pseudophpt 2018
#

# MIPS Toolchain
TOOLCHAIN := /opt/mips/bin/mips64-

# Tools
CC = $(TOOLCHAIN)gcc
AS = $(TOOLCHAIN)as
LD = $(TOOLCHAIN)ld
OBJCOPY = $(TOOLCHAIN)objcopy
AR = $(TOOLCHAIN)ar

# Include directory
INCLUDE = ../headers

# Tool flags
CC_FLAGS = -I$(INCLUDE) -G0 # Includes, no .s* 

AS_FLAGS = -G0 -32 -EB -I$(INCLUDE) # Includes # Big endian

LD_FLAGS = -G0 # No .s*

AR_FLAGS = 

# Files
ARCHIVE = libpseultra.a

OS_SRCS = $(wildcard */*.c)
OS_ASMS = $(wildcard */*.s)

OS_OBJS = $(patsubst %.c, %.o, $(OS_SRCS)) $(patsubst %.s, %.o, $(OS_ASMS))

all: $(ARCHIVE)

$(ARCHIVE): $(OS_OBJS)
	$(AR) rcs $@ $^

$(OS_OBJS): $(OS_SRCS) $(OS_ASMS)
	$(foreach src, $(OS_SRCS), \
		$(CC) $(CC_FLAGS) -c \
		-o $(patsubst %.c, %.o, $(src)) \
		$(src); \
	)	
	$(foreach asm, $(OS_ASMS), \
		$(AS) $(AS_FLAGS) \
		-o $(patsubst %.s, %.o, $(asm)) \
		$(asm); \
	)
