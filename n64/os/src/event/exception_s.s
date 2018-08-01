#
# pseultra/n64/os/src/event/exception_s.s
# Exception handler
# 
# (C) pseudophpt 2018 
#

.include "n64.s.h"

.global __osHandlerStart
.global __osHandlerEnd
.global __osHandleException
.global __osUnmaskInterrupts

.extern __osHandleInterrupt

.macro savereg

lui $k0, %hi(__osExceptionRegSave)
addiu $k0, %lo(__osExceptionRegSave)

.irp reg,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
sw $\reg, (\reg * 4)($k0)
.endr

.endm

.macro loadreg

lui $k0, %hi(__osExceptionRegSave)
addiu $k0, %lo(__osExceptionRegSave)

.irp reg,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
lw $\reg, (\reg * 4)($k0)
.endr

.endm

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

savereg

mfc0 $t0, Cause
andi $t1, $t0, 0x007c

bnez $t1, .handleException # Interrupt code is 0

.handleInterrupt:

andi $a0, $t0, 0xff00
jal __osHandleInterrupt
b .done

.handleException:

.done:

loadreg

eret

.lcomm __osExceptionRegSave, 32 * 4
