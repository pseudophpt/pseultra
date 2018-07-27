#
# pseultra/os/except/handler_s.s
# Exception handler
# 
# (C) pseudophpt 2018 
#

.include "n64.s.h"

.global __osHandlerStart
.global __osHandlerEnd
.global __osHandleException
.global __osUnmaskInterrupts
.global osGetIntMask
.global osSetIntMask
.global osClearIntMask

#
# Unmasks all interrupts
#

__osUnmaskInterrupts:
mfc0 $k0, Status

# MIPS Interrupts

ori $k0, 0xff01 # Unmask all interrupts and enable

or $k0, $k1 
mtc0 $k0, Status

jr $ra # Return

#
# Called on exception 
#

__osHandlerStart:

lui $k0, %hi(__osHandleException)
addiu $k0, %lo(__osHandleException)
jr $k0

__osHandlerEnd:

#
# Called on exception by initial vector
#

__osHandleException:

# I'm going to hold off on writing exception handlers until I get a proper multi-threading implemetation. So for now, it just jumps back to the EPC

eret
