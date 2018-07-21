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
mtc0 $zero, Count # Clear cycle count
mtc0 $zero, Compare # Clear cycle timer compare

# DMA first megabyte of ROM to 0x400
li $t0, PI_DRAM_ADDR_REG | KSEG1
ori $t1, 0x400
sw $t0, 0($t1)

li $t0, PI_CART_ADDR_REG | KSEG1
ori $t1, 0x1000
sw $t0, 0($t1)

li $t0, PI_RD_LEN_REG | KSEG1
li $t1, 0xFFFFFF
sw $t0, 0($t1)

# Unmask RCP interrupts
li $t0, MI_INTR_MASK_REG | KSEG1
ori $t1, 0x555
sw $t1, 0($t0)

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

# Jump to ROM
li $t0, 0x400 | KSEG1
jr $t0
