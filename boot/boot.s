#
# pseultra/boot/boot.s
# Bootcode
# 
# (C) pseudophpt 2018
#

# N64 Definitions
.include "n64.s.h"

# Code begins at 0x40
.org 0x40

# Initialize COP0 registers
mtc0 $zero, Cause # Clear interrupt cause
mtc0 $zero, Compare # Clear compare
mtc0 $zero, Count # Clear cycle count
