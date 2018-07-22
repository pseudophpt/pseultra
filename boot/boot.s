#
# pseultra/boot/boot.s
# Bootcode
# 
# (C) pseudophpt, Nabile Rahmani 2018
#

# N64 Definitions
.include "n64.s.h"

# Code begins at 0x40
.org 0x40

# First stage in RSP DMEM
Stage1Start:

# Initialize COP0 registers
mtc0 $zero, Cause # Clear interrupt cause
mtc0 $zero, Count # Clear cycle count
mtc0 $zero, Compare # Clear cycle timer compare

# DMA boot segment to 0x1000
li $t4, CART_DOM1_ADDR2 | KSEG1
lw $t3, 0x10($t4) # Start of boot segment in ROM
lw $t2, 0x14($t4) # Length of boot segment
addiu $t2, -1

li $t1, PI_DRAM_ADDR_REG | KSEG1
li $t0, 0x1000
sw $t0, 0($t1) # Load at 0x1000

li $t1, PI_CART_ADDR_REG | KSEG1
li $t4, CART_DOM1_ADDR2 
addu $t1, $t4 # Load at boot segment
sw $t3, 0($t1)

li $t1, PI_WR_LEN_REG | KSEG1
sw $t2, 0($t1)

# Unmask RCP interrupts
li $t1, MI_INTR_MASK_REG | KSEG1
ori $t0, $zero, 0x555
sw $t0, 0($t1)

# Clear each RCP interrupt cause bit
li $t0, AI_STATUS_REG | KSEG1
sw $zero, 0($t0)

li $t0, SI_STATUS_REG | KSEG1
sw $zero, 0($t0)

li $t0, PI_STATUS_REG | KSEG1
ori $t1, $zero, 0x02
sw $t1, 0($t0)

li $t0, MI_INIT_MODE_REG | KSEG1
ori $t1, $zero, 0x800
sw $t1, 0($t0)

# Initialize RSP
li $t0, SP_PC_REG | KSEG1
sw $zero, 0($t0)

li $t0, SP_STATUS_REG | KSEG1
li $t1, 0x00aaaaae 
sw $t1, 0($t0)

# Restore registers
li $t0, 0x80000300
sw $s4, 0x00($t0)
sw $s3, 0x04($t0)
sw $s5, 0x0c($t0)
sw $s7, 0x14($t0)

# Copy second stage to RDRAM at 0x300

# The well-regarded GNU toolchain appears to be unable to process the most simple of constants, so I have to do this in two steps.
li $t0, SP_DMEM | KSEG1
ori $t0, (Stage2Start) # Source
li $t1, 0x400 | KSEG0 # Destination
li $t2, SP_DMEM | KSEG1
ori $t2, (Stage2End) # End

.LoadStage2Word:
lw $t3, 0($t0) # From source
sw $t3, 0($t1) # To destination
addiu $t0, 0x04 # Increment locations
addiu $t1, 0x04
bne $t0, $t2, .LoadStage2Word # If not yet at the end, copy another word

li $t0, 0x400 | KSEG0
jr $t0

Stage1End:

Stage2Start:

# Clear RSP DMEM and IMEM
li $t0, SP_DMEM | KSEG1 # DMEM
li $t1, SP_IMEM | KSEG1 # IMEM
li $t2, 0 # Counter
li $t3, 0x400 # Word limit

.ClearSPMEM:
sw $zero, 0($t0)
sw $zero, 0($t1)
addiu $t0, 4
addiu $t1, 4
addiu $t3, 1
beq $t2, $t3, .ClearSPMEM

# Jump to boot segment
li $t0, CART_DOM1_ADDR2 | KSEG0
lw $t0, 8($t0) # Relative offset
li $t1, KSEG0 | 0x1000
addu $t0, $t1 # Add KSEG0
jr $t0

Stage2End:
