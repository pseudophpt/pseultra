/*
 * pseultra/n64/ucode/include/ucode/rsp.h
 * RSP Header
 * 
 * (C) pseudophpt 2018 
 */

/**
 * @file include/ucode/rsp.h
 * @brief RSP Header 
 * @date 20 Aug 2018
 * @author pseudophpt
 *
 * This file defines macros related to the RSP 
 */

#ifndef UCODE_RSP_H_GUARD
#define UCODE_RSP_H_GUARD

#ifdef __asm__

/*
 * RSP COP0 Registers
 */

#define DMA_CACHE $0
#define DMA_DRAM $1
#define DMA_READ_LENGTH $2
#define DMA_WRITE_LENGTH $3
#define SP_STATUS $4
#define DMA_FULL $5
#define DMA_BUSY $6
#define SP_RESERVED $7
#define CMD_START $8
#define CMD_END $9
#define CMD_CURRENT $10
#define CMD_STATUS $11
#define CMD_CLOCK $12
#define CMD_BUSY $13
#define CMD_PIPE_BUSY $14
#define CMD_TMEM_BUSY $15

/*
 * Instructions not defined
 */

.macro undefinst inst
.macro \inst _:vararg
\inst\()_
.endm
.endm

// 64 bit loads/stores
undefinst ldl
undefinst ldr
undefinst lwl
undefinst lwr
undefinst lwu
undefinst swl
undefinst sdl
undefinst sdr
undefinst swr
undefinst ll
undefinst lld
undefinst ldc1
undefinst ldc2
undefinst ld
undefinst sdc1
undefinst sdc2
undefinst sd

// Store conditionals
undefinst sc
undefinst scd

// Likely branches
undefinst beql
undefinst bnel
undefinst blezl
undefinst bgtzl
undefinst bltzl
undefinst bgezl
undefinst bltzall
undefinst bgtzall
undefinst bgezall

// Hi/lo moves
undefinst mfhi
undefinst mthi
undefinst mflo
undefinst mtlo

// 64-bit instructions
undefinst daddi
undefinst daddiu
undefinst dsllv
undefinst dsrlv
undefinst dsrav
undefinst dmult
undefinst dmultu
undefinst ddiv
undefinst ddivu
undefinst dadd
undefinst daddu
undefinst dsub
undefinst dsubu
undefinst dsll
undefinst dsrl
undefinst dsra
undefinst dsll32
undefinst dsrl32
undefinst dsra32

// Mult/div instructions
undefinst mult
undefinst multu
undefinst div
undefinst divu

// No RSP exceptions
undefinst syscall

// Not multiprocessor
undefinst sync

// Branch-on-coprocessor
undefinst bc1f
undefinst bc1t

// Trap instructions
undefinst tge
undefinst tgeu
undefinst tlt
undefinst tltu
undefinst teq
undefinst tne
undefinst tgei
undefinst tgeiu
undefinst tlti
undefinst tltiu
undefinst teqi
undefinst tnei

/*
 * Element registers
 */
#define f 0
#define q0 2
#define q1 3
#define h0 4
#define h1 5
#define h2 6
#define h3 7
#define e0 8
#define e1 9
#define e2 10
#define e3 11
#define e4 12
#define e5 13
#define e6 14
#define e7 15

/*
 * Vector registers 
 */

#define v0 0
#define v1 1
#define v2 2
#define v3 3
#define v4 4
#define v5 5
#define v6 6
#define v7 7
#define v8 8
#define v9 9
#define v10 10
#define v11 11
#define v12 12
#define v13 13
#define v14 14
#define v15 15
#define v16 16
#define v17 17
#define v18 18
#define v19 19
#define v20 20
#define v21 21
#define v22 22
#define v23 23
#define v24 24
#define v25 25
#define v26 26
#define v27 27
#define v28 28
#define v29 29
#define v30 30
#define v31 31

/* 
 * Vector operations modified from libdragon
 */

/** @brief Syntactic sugar for cop2 instuctions */
.macro vecop opcode, vd, vs, vt, element
    cop2 (\element << 21 | \vt << 16 | \vs << 11 | \vd << 6 | \opcode)
.endm

/** @brief Syntactic sugar for lwc2 instuctions */
.macro vecloadop, opcode, vt, element, offset, base
    lwc2 \vt, (\opcode << 11 | \element << 7 | \offset) (\base)
.endm

/** @brief Syntactic sugar for swc2 instuctions */
.macro vecstoreop opcode, vt, element, offset, base
    swc2 \vt, (\opcode << 11 | \element << 7 | \offset) (\base)
.endm

/** @brief Make vector operation */
.macro makevecop name, opcode
    .macro \name vd, vs, vt, element
         vecop \opcode, \vd, \vs, \vt, \element
    .endm
.endm

/** @brief Make vector load operation */
.macro makevecloadop name, opcode
    .macro \name vt, element, offset, base
        loadVector \opcode, \vt, \element, \offset, \base
    .endm
.endm

/** @brief Make vector store operation */
.macro makevecstoreop name, opcode
    .macro \name vt, element, offset, base
         storeVector \opcode, \vt, \element, \offset, \base
    .endm
.endm

/** @brief Vector Absolute Value of Short Elements */
makevecop vabs, 0b010011
/** @brief Vector Add of Short Elements */
makevecop vadd, 0b010000
/** @brief Vector Add Short Elements With Carry */
makevecop vaddc, 0b010100
/** @brief Vector AND of Short Elements */
makevecop vand, 0b010100
/** @brief Vector Select Clip Test High */
makevecop vch, 0b100101
/** @brief Vector Select Clip Test Low */
makevecop vcl, 0b100100
/** @brief Vector Select Crimp Test Low */
makevecop vcr, 0b100110
/** @brief Vector Select Equal */
makevecop veq, 0b100001
/** @brief Vector Select Greater Than or Equal */
makevecop vge, 0b100011
/** @brief Vector Select Less Than */
makevecop vlt, 0b100000
/** @brief Vector Multiply-Accumulate of Signed Fractions */
makevecop vmacf, 0b001000
/** @brief Vector Accumulator Oddification */
makevecop vmacq, 0b001011
/** @brief Vector Multiply-Accumulate of Unsigned Fractions */
makevecop vmacu, 0b001001
/** @brief Vector Multiply-Accumulate of High Partial Products */
makevecop vmadh, 0b001111
/** @brief Vector Multiply-Accumulate of Low Partial Products */
makevecop vmadl, 0b001100
/** @brief Vector Multiply-Accumulate of Mid Partial Products */
makevecop vmadm, 0b001101
/** @brief Vector Multiply-Accumulate of Mid Partial Products */
makevecop vmadn, 0b001110
/** @brief Vector Element Scalar Move */
makevecop vmov, 0b110011
/** @brief Vector Select Merge */
makevecop vmrg, 0b100111
/** @brief Vector Multiply of High Partial Products */
makevecop vmudh, 0b000111
/** @brief Vector Multiply of Low Partial Products */
makevecop vmudl, 0b000100
/** @brief Vector Multiply of Mid Partial Products */
makevecop vmudm, 0b000101
/** @brief Vector Multiply of Mid Partial Products */
makevecop vmudn, 0b000110
/** @brief Vector Multiply of Signed Fractions */
makevecop vmulf, 0b000000
/** @brief Vector Multiply MPEG Quantization */
makevecop vmulq, 0b000011
/** @brief Vector Multiply of Unsigned Fractions */
makevecop vmulu, 0b000001
/** @brief Vector NAND of Short Elements */
makevecop vnand, 0b101001
/** @brief Vector Select Not Equal */
makevecop vne, 0b100010
/** @brief Vector Null Instruction */
makevecop vnop, 0b110111
/** @brief Vector NOR of Short Elements */
makevecop vnor, 0b101011
/** @brief Vector NXOR of Short Elements */
makevecop vnxor, 0b101101
/** @brief Vector OR of Short Elements */
makevecop vor, 0b101010
/** @brief Vector Element Scalar Reciprocal (Single Precision) */
makevecop vrcp, 0b110000
/** @brief Vector Element Scalar Reciprocal (Double Prec. High) */
makevecop vrcph, 0b110010
/** @brief Vector Element Scalar Reciprocal (Double Prec. Low) */
makevecop vrcpl, 0b110001
/** @brief Vector Accumulator DCT Rounding (Negative) */
makevecop vrndn, 0b001010
/** @brief Vector Accumulator DCT Rounding (Positive) */
makevecop vrndp, 0b000010
/** @brief Vector Element Scalar SQRT Reciprocal */
makevecop vrsq, 0b110100
/** @brief Vector Element Scalar SQRT Reciprocal (Double Prec. High) */
makevecop vrsqh, 0b110110
/** @brief Vector Element Scalar SQRT Reciprocal (Double Prec. Low) */
makevecop vrsql, 0b110101
/** @brief Vector Accumulator Read (and Write) */
makevecop vsar, 0b011101
/** @brief Vector Subtraction of Short Elements */
makevecop vsub, 0b010001
/** @brief Vector Subtraction of Short Elements With Carry */
makevecop vsubc, 0b010101
/** @brief Vector XOR of Short Elements */
makevecop vxor, 0b101100

/** @brief Load Byte into Vector Register */
makevecloadop lbv, 0b00000
/** @brief Load Double into Vector Register */
makevecloadop ldv, 0b00011
/** @brief Load Packed Fourth into Vector Register */
makevecloadop lfv, 0b01001
/** @brief Load Packed Half into Vector Register */
makevecloadop lhv, 0b01000
/** @brief Load Long into Vector Register */
makevecloadop llv, 0b00010
/** @brief Load Packed Bytes into Vector Register */
makevecloadop lpv, 0b00110
/** @brief Load Quad into Vector Register */
makevecloadop lqv, 0b00100
/** @brief Load Quad (Rest) into Vector Register */
makevecloadop lrv, 0b00101
/** @brief Load Short into Vector Register */
makevecloadop lsv, 0b00001
/** @brief Load Transpose into Vector Register */
makevecloadop ltv, 0b01011
/** @brief Load Unsigned Packed into Vector Register */
makevecloadop luv, 0b00111

/** @brief Store Byte from Vector Register */
makevecstoreop sbv, 0b00000
/** @brief Store Double from Vector Register */
makevecstoreop sdv, 0b00011
/** @brief Store Packed Fourth from Vector Register */
makevecstoreop sfv, 0b01001
/** @brief Store Packed Half from Vector Register */
makevecstoreop shv, 0b01000
/** @brief Store Long from Vector Register */
makevecstoreop slv, 0b00010
/** @brief Store Packed Bytes from Vector Register */
makevecstoreop spv, 0b00110
/** @brief Store Quad from Vector Register */
makevecstoreop sqv, 0b00100
/** @brief Store Quad (Rest) from Vector Register */
makevecstoreop srv, 0b00101
/** @brief Store Short from Vector Register */
makevecstoreop ssv, 0b00001
/** @brief Store Transpose from Vector Register */
makevecstoreop stv, 0b01011
/** @brief Store Unsigned Packed from Vector Register */
makevecstoreop suv, 0b00111
/** @brief Store Wrapped vector from Vector Register */
makevecstoreop swv, 0b00111

#endif

/*
 * RSP specific instruction definitions
 */
#ifdef __asm__

#endif

#endif
