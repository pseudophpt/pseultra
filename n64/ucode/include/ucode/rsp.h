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

#define vc0 0
#define vc1 1
#define vc2 2
#define vc3 3
#define vc4 4
#define vc5 5
#define vc6 6
#define vc7 7
#define vc8 8
#define vc9 9
#define vc10 10
#define vc11 11
#define vc12 12
#define vc13 13
#define vc14 14
#define vc15 15
#define vc16 16
#define vc17 17
#define vc18 18
#define vc19 19
#define vc20 20
#define vc21 21
#define vc22 22
#define vc23 23
#define vc24 24
#define vc25 25
#define vc26 26
#define vc27 27
#define vc28 28
#define vc29 29
#define vc30 30
#define vc31 31

/* 
 * Vector operations modified from libdragon
 */

/** @brief Syntactic sugar for cop2 instuctions */
.macro vecop opcode, vd, vs, vt, element
    cop2 (\element << 21 | \vt << 16 | \vs << 11 | \vd << 6 | \opcode)
.endm

/** @brief Syntactic sugar for lwc2 instuctions */
.macro vecloadop, opcode, vt, element, offset, base
    lwc2 $\vt, ((\opcode << 11 | \element << 7)) (\base)
    .section .vsl
    .word \offset
    .section .text
.endm

/** @brief Syntactic sugar for swc2 instuctions */
.macro vecstoreop opcode, vt, element, offset, base
    swc2 $\vt, ((\opcode << 11 | \element << 7)) (\base)
    .section .vsl
    .word \offset
    .section .text
.endm

/** @brief Make vector operation */
.macro makevecop name, opcode
    .macro \name vd, vs, vt, element
         vecop \opcode, \vd, \vs, \vt, \element
    .endm
.endm

/** @brief Make vector load operation */
.macro makevecloadop name, opcode, shift
    .macro \name vt, element, offset, base
        vecloadop \opcode, \vt, \element, \offset, \base
    .endm
.endm

/** @brief Make vector store operation */
.macro makevecstoreop name, opcode, shift
    .macro \name vt, element, offset, base
         vecstoreop \opcode, \vt, \element, \offset, \base
    .endm
.endm

/** @brief Vector Absolute Value of Short Elements */
makevecop vabs, 0x13
/** @brief Vector Add of Short Elements */
makevecop vadd, 0x10
/** @brief Vector Add Short Elements With Carry */
makevecop vaddc, 0x14
/** @brief Vector AND of Short Elements */
makevecop vand, 0x28
/** @brief Vector Select Clip Test High */
makevecop vch, 0x25
/** @brief Vector Select Clip Test Low */
makevecop vcl, 0x24
/** @brief Vector Select Crimp Test Low */
makevecop vcr, 0x26
/** @brief Vector Select Equal */
makevecop veq, 0x21
/** @brief Vector Select Greater Than or Equal */
makevecop vge, 0x23
/** @brief Vector Select Less Than */
makevecop vlt, 0x20
/** @brief Vector Multiply-Accumulate of Signed Fractions */
makevecop vmacf, 0x08
/** @brief Vector Accumulator Oddification */
makevecop vmacq, 0x0b
/** @brief Vector Multiply-Accumulate of Unsigned Fractions */
makevecop vmacu, 0x09
/** @brief Vector Multiply-Accumulate of High Partial Products */
makevecop vmadh, 0x0f
/** @brief Vector Multiply-Accumulate of Low Partial Products */
makevecop vmadl, 0x0c
/** @brief Vector Multiply-Accumulate of Mid Partial Products */
makevecop vmadm, 0x0d
/** @brief Vector Multiply-Accumulate of Mid Partial Products */
makevecop vmadn, 0x0e
/** @brief Vector Element Scalar Move */
makevecop vmov, 0x33
/** @brief Vector Select Merge */
makevecop vmrg, 0x27
/** @brief Vector Multiply of High Partial Products */
makevecop vmudh, 0x07
/** @brief Vector Multiply of Low Partial Products */
makevecop vmudl, 0x04
/** @brief Vector Multiply of Mid Partial Products */
makevecop vmudm, 0x05
/** @brief Vector Multiply of Mid Partial Products */
makevecop vmudn, 0x06
/** @brief Vector Multiply of Signed Fractions */
makevecop vmulf, 0x00
/** @brief Vector Multiply MPEG Quantization */
makevecop vmulq, 0x03
/** @brief Vector Multiply of Unsigned Fractions */
makevecop vmulu, 0x01
/** @brief Vector NAND of Short Elements */
makevecop vnand, 0x29
/** @brief Vector Select Not Equal */
makevecop vne, 0x22
/** @brief Vector Null Instruction */
makevecop vnop, 0x37
/** @brief Vector NOR of Short Elements */
makevecop vnor, 0x2b
/** @brief Vector NXOR of Short Elements */
makevecop vnxor, 0x2d
/** @brief Vector OR of Short Elements */
makevecop vor, 0x2a
/** @brief Vector Element Scalar Reciprocal (Single Precision) */
makevecop vrcp, 0x30
/** @brief Vector Element Scalar Reciprocal (Double Prec. High) */
makevecop vrcph, 0x32
/** @brief Vector Element Scalar Reciprocal (Double Prec. Low) */
makevecop vrcpl, 0x31
/** @brief Vector Accumulator DCT Rounding (Negative) */
makevecop vrndn, 0x0a
/** @brief Vector Accumulator DCT Rounding (Positive) */
makevecop vrndp, 0x02
/** @brief Vector Element Scalar SQRT Reciprocal */
makevecop vrsq, 0x34
/** @brief Vector Element Scalar SQRT Reciprocal (Double Prec. High) */
makevecop vrsqh, 0x36
/** @brief Vector Element Scalar SQRT Reciprocal (Double Prec. Low) */
makevecop vrsql, 0x35
/** @brief Vector Accumulator Read (and Write) */
makevecop vsar, 0x1d
/** @brief Vector Subtraction of Short Elements */
makevecop vsub, 0x11
/** @brief Vector Subtraction of Short Elements With Carry */
makevecop vsubc, 0x15
/** @brief Vector XOR of Short Elements */
makevecop vxor, 0x2c

/** @brief Load Byte into Vector Register */
makevecloadop lbv, 0x00
/** @brief Load Double into Vector Register */
makevecloadop ldv, 0x03
/** @brief Load Packed Fourth into Vector Register */
makevecloadop lfv, 0x09
/** @brief Load Packed Half into Vector Register */
makevecloadop lhv, 0x08
/** @brief Load Long into Vector Register */
makevecloadop llv, 0x02
/** @brief Load Packed Bytes into Vector Register */
makevecloadop lpv, 0x06
/** @brief Load Quad into Vector Register */
makevecloadop lqv, 0x04
/** @brief Load Quad (Rest) into Vector Register */
makevecloadop lrv, 0x05
/** @brief Load Short into Vector Register */
makevecloadop lsv, 0x01
/** @brief Load Transpose into Vector Register */
makevecloadop ltv, 0x0b
/** @brief Load Unsigned Packed into Vector Register */
makevecloadop luv, 0x07

/** @brief Store Byte from Vector Register */
makevecstoreop sbv, 0x00
/** @brief Store Double from Vector Register */
makevecstoreop sdv, 0x03
/** @brief Store Packed Fourth from Vector Register */
makevecstoreop sfv, 0x09
/** @brief Store Packed Half from Vector Register */
makevecstoreop shv, 0x08
/** @brief Store Long from Vector Register */
makevecstoreop slv, 0x02
/** @brief Store Packed Bytes from Vector Register */
makevecstoreop spv, 0x06
/** @brief Store Quad from Vector Register */
makevecstoreop sqv, 0x04
/** @brief Store Quad (Rest) from Vector Register */
makevecstoreop srv, 0x05
/** @brief Store Short from Vector Register */
makevecstoreop ssv, 0x01
/** @brief Store Transpose from Vector Register */
makevecstoreop stv, 0x0b
/** @brief Store Unsigned Packed from Vector Register */
makevecstoreop suv, 0x07
/** @brief Store Wrapped vector from Vector Register */
makevecstoreop swv, 0x07

/*
 * Special instructions
 */

#endif

/*
 * RSP specific instruction definitions
 */
#ifdef __asm__

#endif

#endif
