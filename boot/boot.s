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
li $t1, 0x10000000 | KSEG1
lw $t0, 8($t1) # Load the boot address from the cartridge header.
li $t1, PI_DRAM_ADDR_REG | KSEG1
sw $t0, 0($t1)

li $t1, PI_CART_ADDR_REG | KSEG1
li $t0, 0x10001000 # 0x1000 in ROM
sw $t0, 0($t1)

li $t1, PI_WR_LEN_REG | KSEG1
li $t0, 0xFFFFF # One megabyte
sw $t0, 0($t1)

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

# Jump to ROM
li $t0, 0x10000000 | KSEG1
lw $t0, 8($t0)
jr $t0
