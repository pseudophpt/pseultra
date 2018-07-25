#
# pseultra/os/except/handler_s.s
# Exception handler
# 
# (C) pseudophpt 2018 
#

.include "n64.s.h"

__osHandlerStart:

li $k0, __osHandleException
jr $k0

__osHandlerEnd:

__osHandleException:

# I'm going to hold off on writing exception handlers until I get a proper multi-threading implemetation. So for now, it just jumps back to the EPC

mfc0 $k0, EPC
jr $k0

#addiu $sp, -(0x4 * 4) // Save 4 tx registers
#sw $t0, 0($sp)
#sw $t1, 4($sp)
#sw $t2, 8($sp)



#lw $t0, ($sp)

#lw $t1, ($sp)
#lw $t2, ($sp)
#// Crash

#.lock:
#b .lock
