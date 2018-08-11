/*
 * pseultra/include/n64.h
 * N64 definitions for C
 * 
 * (C) pseudophpt 2018
 */

/**
 * @file include/n64.h
 * @brief N64 definitions header
 * @date 3 Aug 2018
 * @author pseudophpt
 * @todo Finish documentation
 *
 * This file provides definitions for structs, constants, and functions related to the N64
 */

#ifndef N64_H_GUARD
#define N64_H_GUARD

/* 
 * ROM Header Format
 */

#ifndef __asm__

#include <stdint.h>

/** @brief Struct describing the ROM header */
typedef struct __attribute__((__packed__)) rom_header_t {
    /** @brief PI registers */
    uint32_t pi_regs;
    /** @brief CPU clock rate*/
    uint32_t clock_rate;
    /** @brief Address to jump to after IPL3 bootcode */
    uint32_t boot_address;
    /** @brief Release number */
    uint32_t release;
    /** @brief Start of boot segment in ROM */
    uint32_t rom_start;
    /** @brief Length of boot segment in ROM */
    uint32_t rom_length;
    /** @brief Unused */
    uint32_t padding [2];
    /** @brief Game name */
    char image_name [0x14];
    /** @brief Unused */
    uint8_t padding2 [7];
    /** @brief Manufacturer ID */
    uint8_t manufacturer_id;
    /** @brief Cartridge ID */
    uint16_t cart_id;
    /** @brief Country code */
    uint8_t country;
    /** @brief Unused */
    uint8_t padding3;
} rom_header;

#endif 

/** @brief Values for the PI */
#define PI_VALUES 0x80371240

/** @brief Coprocesor 0 status register interrupt enabled bit */
#define N64_COP0_STATUS_IE 0x1

/** @brief Coprocesor 0 status register exception level bit */
#define N64_COP0_STATUS_EXL 0x2

/** @brief Coprocesor 0 status register error level bit */
#define N64_COP0_STATUS_ERL 0x4

/** @brief Coprocesor 0 status register mode bits */
#define N64_COP0_STATUS_KSU 0x18

/** @brief Coprocesor 0 status register user mode bits for KSU */
#define N64_COP0_STATUS_KSU_USER 0x10

/** @brief Coprocesor 0 status register supervisor mode bits for KSU */
#define N64_COP0_STATUS_KSU_SUPERVISOR 0x08

/** @brief Coprocesor 0 status register kernel mode bits for KSU */
#define N64_COP0_STATUS_KSU_KERNEL 0x00

/** @brief Coprocesor 0 status register 64-bit operations in user mode enable bit */
#define N64_COP0_STATUS_UX 0x20

/** @brief Coprocesor 0 status register 64-bit operations in supervisor mode enable bit */
#define N64_COP0_STATUS_SX 0x40

/** @brief Coprocesor 0 status register 64-bit operations in kernel mode enable bit */
#define N64_COP0_STATUS_KX 0x80

/** @brief Coprocesor 0 status register interrupt mask bits */
#define N64_COP0_STATUS_IM 0xFF00

/** @brief Coprocesor 0 status register interrupt 0 mask bit */
#define N64_COP0_STATUS_IM0 0x0100

/** @brief Coprocesor 0 status register interrupt 1 mask bit */
#define N64_COP0_STATUS_IM1 0x0200

/** @brief Coprocesor 0 status register interrupt 2 mask bit */
#define N64_COP0_STATUS_IM2 0x0400

/** @brief Coprocesor 0 status register interrupt 3 mask bit */
#define N64_COP0_STATUS_IM3 0x0800

/** @brief Coprocesor 0 status register interrupt 4 mask bit */
#define N64_COP0_STATUS_IM4 0x1000

/** @brief Coprocesor 0 status register interrupt 5 mask bit */
#define N64_COP0_STATUS_IM5 0x2000

/** @brief Coprocesor 0 status register interrupt 6 mask bit */
#define N64_COP0_STATUS_IM6 0x4000

/** @brief Coprocesor 0 status register interrupt 7 mask bit */
#define N64_COP0_STATUS_IM7 0x8000

/** @brief Coprocesor 0 status register interrupt mask all bits */
#define N64_COP0_STATUS_IM_ALL 0xFF00

/** @brief Coprocesor 0 status register diagnostic status bits */
#define N64_COP0_STATUS_DS 0x1FF0000

/** @brief Coprocesor 0 status register reverse endian bit */
#define N64_COP0_STATUS_RE 0x2000000

/** @brief Coprocesor 0 status register additional fp registers bit */
#define N64_COP0_STATUS_FR 0x4000000

/** @brief Coprocesor 0 status register low power mode bit */
#define N64_COP0_STATUS_RP 0x8000000

/** @brief Coprocesor 0 status register COP0 usable bit */
#define N64_COP0_STATUS_COP0_USABLE 0x10000000

/** @brief Coprocesor 0 status register COP1 usable bit */
#define N64_COP0_STATUS_COP1_USABLE 0x20000000

/** @brief Coprocesor 0 status register COP2 usable bit */
#define N64_COP0_STATUS_COP2_USABLE 0x40000000

/** @brief Coprocesor 0 status register COP3 usable bit */
#define N64_COP0_STATUS_COP3_USABLE 0x80000000

/** @brief Coprocesor 0 cause register exception code bits */
#define N64_COP0_CAUSE_EXC_CODE 0x7C

/** @brief Coprocesor 0 cause register Interrupt exception code */
#define N64_COP0_CAUSE_EXC_CODE_INT 0x0

/** @brief Coprocesor 0 cause register TLB modification exception code */
#define N64_COP0_CAUSE_EXC_CODE_MOD 0x4

/** @brief Coprocesor 0 cause register TLB miss on load exception code */
#define N64_COP0_CAUSE_EXC_CODE_TLBL 0x8

/** @brief Coprocesor 0 cause register TLB Miss on store exception code */
#define N64_COP0_CAUSE_EXC_CODE_TLBS 0xC

/** @brief Coprocesor 0 cause register Address error on load exception code */
#define N64_COP0_CAUSE_EXC_CODE_ADEL 0x10

/** @brief Coprocesor 0 cause register Address error on store exception code */
#define N64_COP0_CAUSE_EXC_CODE_ADES 0x14

/** @brief Coprocesor 0 cause register Bus error on instruction fetch exception code */
#define N64_COP0_CAUSE_EXC_CODE_IBE 0x18

/** @brief Coprocesor 0 cause register Bus error on data reference exception code */
#define N64_COP0_CAUSE_EXC_CODE_DBE 0x1C

/** @brief Coprocesor 0 cause register Syscall exception code */
#define N64_COP0_CAUSE_EXC_CODE_SYS 0x20

/** @brief Coprocesor 0 cause register Breakpoint exception code */
#define N64_COP0_CAUSE_EXC_CODE_BP 0x24

/** @brief Coprocesor 0 cause register Reserved instruction exception code */
#define N64_COP0_CAUSE_EXC_CODE_RI 0x28

/** @brief Coprocesor 0 cause register Coprocessor unusable exception code */
#define N64_COP0_CAUSE_EXC_CODE_CPU 0x2C

/** @brief Coprocesor 0 cause register Arithmetic overflow exception code */
#define N64_COP0_CAUSE_EXC_CODE_OV 0x30

/** @brief Coprocesor 0 cause register Trap exception code */
#define N64_COP0_CAUSE_EXC_CODE_TR 0x34

/** @brief Coprocesor 0 cause register Floating point exception code */
#define N64_COP0_CAUSE_EXC_CODE_FPE 0x3C

/** @brief Coprocesor 0 cause register Watch exception code */
#define N64_COP0_CAUSE_EXC_CODE_WATCH 0x5C

/** @brief Coprocesor 0 cause register interrupt bits */
#define N64_COP0_CAUSE_IP 0xFF00

/** @brief Coprocesor 0 cause register interrupt 0 bit */
#define N64_COP0_CAUSE_IP0 0x0100

/** @brief Coprocesor 0 cause register interrupt 1 bit */
#define N64_COP0_CAUSE_IP1 0x0200

/** @brief Coprocesor 0 cause register interrupt 2 bit */
#define N64_COP0_CAUSE_IP2 0x0400

/** @brief Coprocesor 0 cause register interrupt 3 bit */
#define N64_COP0_CAUSE_IP3 0x0800

/** @brief Coprocesor 0 cause register interrupt 4 bit */
#define N64_COP0_CAUSE_IP4 0x1000

/** @brief Coprocesor 0 cause register interrupt 5 bit */
#define N64_COP0_CAUSE_IP5 0x2000

/** @brief Coprocesor 0 cause register interrupt 6 bit */
#define N64_COP0_CAUSE_IP6 0x4000

/** @brief Coprocesor 0 cause register interrupt 7 bit */
#define N64_COP0_CAUSE_IP7 0x8000

/** @brief Coprocesor 0 cause register Number of coprocessor which is unusable */
#define N64_COP0_CAUSE_COP_NUMBER 0x30000000

/** @brief Coprocesor 0 cause register in branch delay or not */
#define N64_COP0_CAUSE_BD 0x80000000

/** @brief NMI exception vector */
#define N64_EXC_VEC_NMI 0xBFC00000

/** @brief TLB miss exception vector */
#define N64_EXC_VEC_TLB_MISS 0x80000000

/** @brief XTLB miss exception vector */
#define N64_EXC_VEC_XTLB_MISS 0x80000080

/** @brief General exception vector */
#define N64_EXC_VEC_GENERAL 0x80000180

/** @brief KUSEG Address (TLB mapped) */
#define N64_KUSEG 0x00000000

/** @brief KSEG0 Address (Cached) */
#define N64_KSEG0 0x80000000

/** @brief KUSEG Address (Uncached) */
#define N64_KSEG1 0xA0000000

/** @brief KSSEG Address (TLB mapped) */
#define N64_KSSEG 0xC0000000

/** @brief KSEG3 Address (TLB mapped) */
#define N64_KSEG3 0xE0000000

/** @brief Macro to transform physical address into KUSEG address */
#define N64_KUSEG_ADDR(x) (N64_KUSEG | x)

/** @brief Macro to transform physical address into KSEG0 address */
#define N64_KSEG0_ADDR(x) (N64_KSEG0 | x)

/** @brief Macro to transform physical address into KSEG1 address */
#define N64_KSEG1_ADDR(x) (N64_KSEG1 | x)

/** @brief Macro to transform physical address into KSSEG address */
#define N64_KSSEG_ADDR(x) (N64_KSSEG | x)

/** @brief Macro to transform physical address into KSEG3 address */
#define N64_KSEG3_ADDR(x) (N64_KSEG3 | x)

/** @brief RDRAM Base register */
#define N64_RDRAM_BASE_REG 0x03F00000

#define N64_RDRAM_CONFIG_REG 0x03F00000 
#define N64_RDRAM_DEVICE_TYPE_REG 0x03F00000 
#define N64_RDRAM_DEVICE_ID_REG 0x03F00004
#define N64_RDRAM_DELAY_REG 0x03F00008 
#define N64_RDRAM_MODE_REG 0x03F0000C 
#define N64_RDRAM_REF_INTERVAL_REG 0x03F00010 
#define N64_RDRAM_REF_ROW_REG 0x03F00014 
#define N64_RDRAM_RAS_INTERVAL_REG 0x03F00018 
#define N64_RDRAM_MIN_INTERVAL_REG 0x03F0001C 
#define N64_RDRAM_ADDR_SELECT_REG 0x03F00020 
#define N64_RDRAM_DEVICE_MANUF_REG 0x03F00024 

/** @brief SP Base register */
#define N64_SP_BASE_REG 0x04040000

/** @brief Beginning of SP DMEM */
#define N64_SP_DMEM 0x04000000 

/** @brief Beginning of SP IMEM */
#define N64_SP_IMEM 0x04001000 

/** @brief SP MEM Address for SP DMA 
 * 
 * To set this register, write a u32 to this macro address with the following value:
 * N64_SP_MEM_ADDR_REG_ADDR(<offset in SP mem>) | N64_SP_MEM_ADDR_REG_[D/I]MEM
 *
 * @see N64_SP_MEM_ADDR_REG_ADDR
 * @see N64_SP_MEM_ADDR_REG_DMEM
 * @see N64_SP_MEM_ADDR_REG_IMEM
 */
#define N64_SP_MEM_ADDR_REG 0x04040000
/** @brief Convert to SP MEM address for N64_SP_MEM_ADDR_REG */
#define N64_SP_MEM_ADDR_REG_ADDR(x) (x & 0xFFF)
/** @brief Tells N64_SP_MEM_ADDR_REG to DMA to/from DMEM*/
#define N64_SP_MEM_ADDR_REG_DMEM 0x0000
/** @brief Tells N64_SP_MEM_ADDR_REG to DMA to/from IMEM*/
#define N64_SP_MEM_ADDR_REG_IMEM 0x1000

/** @brief RDRAM Address for SP DMA 
 *
 * To set this register, write a u32 to this macro address with the following value:
 * N64_SP_DRAM_ADDR_REG_ADDR(<rdram address>)
 *
 * @see N64_SP_DRAM_ADDR_REG_ADDR
 */
#define N64_SP_DRAM_ADDR_REG 0x04040004 
/** @brief Convert to DRAM address for N64_SP_DRAM_ADDR_REG_ADDR */
#define N64_SP_DRAM_ADDR_REG_ADDR(x) (x & 0x00FFFFFF)

/** @brief Read length for SP DMA 
 *
 * To set this register, write a u32 to this macro address with the following value:
 * N64_SP_RD_LEN_REG_LENGTH(<length>) | N64_SP_RD_LEN_REG_COUNT(<count>) | N64_SP_RD_LEN_REG_SKIP(<skip>)
 *
 * @see N64_SP_RD_LEN_REG_LENGTH
 * @see N64_SP_RD_LEN_REG_COUNT
 * @see N64_SP_RD_LEN_REG_SKIP
 */
#define N64_SP_RD_LEN_REG 0x04040008 
/** @brief Convert to read length for N64_SP_RD_LEN_REG */
#define N64_SP_RD_LEN_REG_LENGTH(x) (x & 0xFFF)
/** @brief Convert to count for N64_SP_RD_LEN_REG */
#define N64_SP_RD_LEN_REG_COUNT(x) ((x & 0xFF) << 12)
/** @brief Convert to skip for N64_SP_RD_LEN_REG */
#define N64_SP_RD_LEN_REG_SKIP(x) ((x & 0xFFF) << 20)

/** @brief Write length for SP DMA 
 *
 * To set this register, write a u32 to this macro address with the following value:
 * N64_SP_WR_LEN_REG_LENGTH(<length>) | N64_SP_WR_LEN_REG_COUNT(<count>) | N64_SP_WR_LEN_REG_SKIP(<skip>)
 *
 * @see N64_SP_WR_LEN_REG_LENGTH
 * @see N64_SP_WR_LEN_REG_COUNT
 * @see N64_SP_WR_LEN_REG_SKIP
 */
#define N64_SP_WR_LEN_REG 0x0404000C 
/** @brief Convert to read length for N64_SP_WR_LEN_REG */
#define N64_SP_WR_LEN_REG_LENGTH(x) (x & 0xFFF)
/** @brief Convert to count for N64_SP_WR_LEN_REG */
#define N64_SP_WR_LEN_REG_COUNT(x) ((x & 0xFF) << 12)
/** @brief Convert to skip for N64_SP_WR_LEN_REG */
#define N64_SP_WR_LEN_REG_SKIP(x) ((x & 0xFFF) << 20)

/** @brief SP status register 
 *
 * To set this register, write a u32 to this macro address with the following value:
 * [N64_SP_STATUS_REG_[CLEAR/SET]_HALT |] [N64_SP_STATUS_REG_CLEAR_BROKE |] [N64_SP_STATUS_REG_[CLEAR/SET]_INTR |] [N64_SP_STATUS_REG_[CLEAR/SET]_SSTEP |] [N64_SP_STATUS_REG_[CLEAR/SET]_INTR_ON_BREAK |] [N64_SP_STATUS_REG_[CLEAR/SET]_SIG[0/1/2/3/4/5/6/7]]
 * 
 * To parse the contents of this register, read a u32 from this macro address and mask the following desired bits:
 * [N64_SP_STATUS_REG_HALT |] [N64_SP_STATUS_REG_BROKE |] [N64_SP_STATUS_REG_DMA_BUSY |] [N64_SP_STATUS_REG_DMA_FULL |] [N64_SP_STATUS_REG_IO_FULL |] [N64_SP_STATUS_REG_SSTEP |] [N64_SP_STATUS_REG_INTR_ON_BREAK |] [N64_STATUS_REG_SIG[0/1/2/3/4/5/6/7]]
 *
 * @see N64_SP_STATUS_REG_CLEAR_HALT
 * @see N64_SP_STATUS_REG_SET_HALT
 * @see N64_SP_STATUS_REG_CLEAR_BROKE
 * @see N64_SP_STATUS_REG_CLEAR_INTR
 * @see N64_SP_STATUS_REG_SET_INTR
 * @see N64_SP_STATUS_REG_CLEAR_SSTEP
 * @see N64_SP_STATUS_REG_SET_SSTEP
 * @see N64_SP_STATUS_REG_CLEAR_INTR_ON_BREAK
 * @see N64_SP_STATUS_REG_SET_INTR_ON_BREAK
 * @see N64_SP_STATUS_REG_CLEAR_SIG0
 * @see N64_SP_STATUS_REG_SET_SIG0
 * @see N64_SP_STATUS_REG_CLEAR_SIG1
 * @see N64_SP_STATUS_REG_SET_SIG1
 * @see N64_SP_STATUS_REG_CLEAR_SIG2
 * @see N64_SP_STATUS_REG_SET_SIG2
 * @see N64_SP_STATUS_REG_CLEAR_SIG3
 * @see N64_SP_STATUS_REG_SET_SIG3
 * @see N64_SP_STATUS_REG_CLEAR_SIG4
 * @see N64_SP_STATUS_REG_SET_SIG4
 * @see N64_SP_STATUS_REG_CLEAR_SIG5
 * @see N64_SP_STATUS_REG_SET_SIG5
 * @see N64_SP_STATUS_REG_CLEAR_SIG6
 * @see N64_SP_STATUS_REG_SET_SIG6
 * @see N64_SP_STATUS_REG_CLEAR_SIG7
 * @see N64_SP_STATUS_REG_HALT
 * @see N64_SP_STATUS_REG_BROKE
 * @see N64_SP_STATUS_REG_DMA_BUSY
 * @see N64_SP_STATUS_REG_DMA_FULL
 * @see N64_SP_STATUS_REG_SSTEP
 * @see N64_SP_STATUS_REG_INTR_ON_BREAK
 * @see N64_SP_STATUS_REG_SIG0
 * @see N64_SP_STATUS_REG_SIG1
 * @see N64_SP_STATUS_REG_SIG2
 * @see N64_SP_STATUS_REG_SIG3
 * @see N64_SP_STATUS_REG_SIG4
 * @see N64_SP_STATUS_REG_SIG5
 * @see N64_SP_STATUS_REG_SIG6
 * @see N64_SP_STATUS_REG_SIG7
 *
 */
#define N64_SP_STATUS_REG 0x04040010  
/** @brief Clear halt bit in N64_SP_STATUS_REG */
#define N64_SP_STATUS_REG_CLEAR_HALT 0x1
/** @brief Set halt bit in N64_SP_STATUS_REG */
#define N64_SP_STATUS_REG_SET_HALT 0x2
/** @brief Clear broke bit in N64_SP_STATUS_REG */
#define N64_SP_STATUS_REG_CLEAR_BROKE 0x4
/** @brief Clear interrupt bit in N64_SP_STATUS_REG */
#define N64_SP_STATUS_REG_CLEAR_INTR 0x8
/** @brief Set interrupt bit in N64_SP_STATUS_REG */
#define N64_SP_STATUS_REG_SET_INTR 0x10
/** @brief Clear single step bit in N64_SP_STATUS_REG */
#define N64_SP_STATUS_REG_CLEAR_SSTEP 0x20
/** @brief Set single step bit in N64_SP_STATUS_REG */
#define N64_SP_STATUS_REG_SET_SSTEP 0x40
/** @brief Clear interrupt on break bit in N64_SP_STATUS_REG */
#define N64_SP_STATUS_REG_CLEAR_INTR_ON_BREAK 0x80
/** @brief Set interrupt on break bit in N64_SP_STATUS_REG */
#define N64_SP_STATUS_REG_SET_INTR_ON_BREAK 0x100
/** @brief Clear signal 0 in N64_SP_STATUS_REG */
#define N64_SP_STATUS_REG_CLEAR_SIG0 0x200
/** @brief Set signal 0 in N64_SP_STATUS_REG */
#define N64_SP_STATUS_REG_SET_SIG0 0x400
/** @brief Clear signal 1 in N64_SP_STATUS_REG */
#define N64_SP_STATUS_REG_CLEAR_SIG1 0x800
/** @brief Set signal 1 in N64_SP_STATUS_REG */
#define N64_SP_STATUS_REG_SET_SIG1 0x1000
/** @brief Clear signal 2 in N64_SP_STATUS_REG */
#define N64_SP_STATUS_REG_CLEAR_SIG2 0x2000
/** @brief Set signal 2 in N64_SP_STATUS_REG */
#define N64_SP_STATUS_REG_SET_SIG2 0x4000
/** @brief Clear signal 3 in N64_SP_STATUS_REG */
#define N64_SP_STATUS_REG_CLEAR_SIG3 0x8000
/** @brief Set signal 3 in N64_SP_STATUS_REG */
#define N64_SP_STATUS_REG_SET_SIG3 0x10000
/** @brief Clear signal 4 in N64_SP_STATUS_REG */
#define N64_SP_STATUS_REG_CLEAR_SIG4 0x20000
/** @brief Set signal 4 in N64_SP_STATUS_REG */
#define N64_SP_STATUS_REG_SET_SIG4 0x40000
/** @brief Clear signal 5 in N64_SP_STATUS_REG */
#define N64_SP_STATUS_REG_CLEAR_SIG5 0x80000
/** @brief Set signal 5 in N64_SP_STATUS_REG */
#define N64_SP_STATUS_REG_SET_SIG5 0x100000
/** @brief Clear signal 6 in N64_SP_STATUS_REG */
#define N64_SP_STATUS_REG_CLEAR_SIG6 0x200000
/** @brief Set signal 6 in N64_SP_STATUS_REG */
#define N64_SP_STATUS_REG_SET_SIG6 0x400000
/** @brief Clear signal 7 in N64_SP_STATUS_REG */
#define N64_SP_STATUS_REG_CLEAR_SIG7 0x800000
/** @brief Set signal 7 in N64_SP_STATUS_REG */
#define N64_SP_STATUS_REG_SET_SIG7 0x1000000
/** @brief Halt bit in N64_SP_STATUS_REG */
#define N64_SP_STATUS_REG_HALT 0x1
/** @brief Broke bit in N64_SP_STATUS_REG */
#define N64_SP_STATUS_REG_BROKE 0x2
/** @brief DMA busy in N64_SP_STATUS_REG */
#define N64_SP_STATUS_REG_DMA_BUSY 0x4
/** @brief DMA full in N64_SP_STATUS_REG */
#define N64_SP_STATUS_REG_DMA_FULL 0x8
/** @brief IO full in N64_SP_STATUS_REG */
#define N64_SP_STATUS_REG_IO_FULL 0x10
/** @brief Single step bit in N64_SP_STATUS_REG */
#define N64_SP_STATUS_REG_SSTEP 0x20
/** @brief Interrupt on break bit in N64_SP_STATUS_REG */
#define N64_SP_STATUS_REG_INTR_ON_BREAK 0x40
/** @brief Signal 0 in N64_SP_STATUS_REG */
#define N64_SP_STATUS_REG_SIG0 0x80
/** @brief Signal 1 in N64_SP_STATUS_REG */
#define N64_SP_STATUS_REG_SIG1 0x100
/** @brief Signal 2 in N64_SP_STATUS_REG */
#define N64_SP_STATUS_REG_SIG2 0x200
/** @brief Signal 3 in N64_SP_STATUS_REG */
#define N64_SP_STATUS_REG_SIG3 0x400
/** @brief Signal 4 in N64_SP_STATUS_REG */
#define N64_SP_STATUS_REG_SIG4 0x800
/** @brief Signal 5 in N64_SP_STATUS_REG */
#define N64_SP_STATUS_REG_SIG5 0x1000
/** @brief Signal 6 in N64_SP_STATUS_REG */
#define N64_SP_STATUS_REG_SIG6 0x2000
/** @brief Signal 7 in N64_SP_STATUS_REG */
#define N64_SP_STATUS_REG_SIG7 0x4000

/** @brief SP DMA FULL register */
#define N64_SP_DMA_FULL_REG 0x04040014 

/** @brief SP DMA BUSY register */
#define N64_SP_DMA_BUSY_REG 0x04040018 

/** @brief SP DMA Semaphore 
 *
 * To acquire the semaphore, simply read the u32 pointed to by this address (assuming it can be acquired). To clear it, write to the u32 pointed to by this macro
 */
#define N64_SP_SEMAPHORE_REG 0x0404001C 

/** @brief SP Program Counter 
 *
 * To set this register, write a u32 to this macro address with the following value:
 * N64_SP_PC_REG_PC(<program counter>)
 * 
 * @see N64_SP_PC_REG_PC
 */
#define N64_SP_PC_REG 0x04080000
/** @brief Convert to PC value for N64_SP_PC_REG */
#define N64_SP_PC_REG_PC(x) (x & 0xFFF)

/** @brief SP IMEM BIST Register */
#define N64_SP_IBIST_REG 0x04080004

/** @brief DP command base register */
#define N64_DPC_BASE_REG 0x04100000

/** @brief DP command start register
 *
 * To set this register, write a u32 to this macro address with the following value:
 *
 * N64_DPC_START_REG_ADDR(<address>)
 *
 * @see N64_DPC_START_REG_ADDR
 */
#define N64_DPC_START_REG 0x04100000 
/** @brief Convert to address for N64_DPC_START_REG */
#define N64_DPC_START_REG_ADDR(x) (x & 0x00FFFFFF)

/** @brief DP command end register
 *
 * To set this register, write a u32 to this macro address with the following value:
 *
 * N64_DPC_END_REG_ADDR(<address>)
 *
 * @see N64_DPC_END_REG_ADDR
 */
#define N64_DPC_END_REG 0x04100004 
/** @brief Convert to address for N64_DPC_END_REG */
#define N64_DPC_END_REG_ADDR(x) (x & 0x00FFFFFF)

/** @brief DP command current register
 *
 * To set this register, write a u32 to this macro address with the following value:
 *
 * N64_DPC_CURRENT_REG_ADDR(<address>)
 *
 * @see N64_DPC_CURRENT_REG_ADDR
 */
#define N64_DPC_CURRENT_REG 0x04100008
/** @brief Convert to address for N64_DPC_CURRENT_REG */
#define N64_DPC_CURRENT_REG_ADDR(x) (x & 0x00FFFFFF)

/** @brief DP command status register 
 *
 * To set this register, write a u32 to this macro address with the following value:
 * [N64_DPC_STATUS_REG_[CLEAR/SET]_XBUS_DMEM_DMA |] [N64_DPC_STATUS_REG_[CLEAR/SET]_FREEZE |] [N64_DPC_STATUS_REG_[CLEAR/SET]_FLUSH |] [N64_DPC_STATUS_REG_CLEAR_TMEM_CTR |] [N64_DPC_STATUS_REG_CLEAR_PIPE_CTR |] [N64_DPC_STATUS_REG_CLEAR_CMD_CTR |] [N64_DPC_STATUS_REG_CLEAR_CLOCK_CTR]
 * 
 * To parse the contents of this register, read a u32 from this macro address and mask the following desired bits
 * [N64_DPC_STATUS_REG_XBUS_DMEM_DMA |] [N64_DPC_STATUS_REG_FREEZE |] [N64_DPC_STATUS_REG_FLUSH |] [N64_DPC_STATUS_REG_START_GCLK |] [N64_DPC_STATUS_REG_TMEM_BUSY |] [N64_DPC_STATUS_REG_PIPE_BUSY |] [N64_DPC_STATUS_REG_CMD_BUSY |] [N64_DPC_STATUS_REG_CBUF_READY |] [N64_DPC_STATUS_REG_DMA_BUSY |] [N64_DPC_STATUS_REG_END_VALID |] [N64_DPC_STATUS_REG_START_VALID]
 *
 * @see N64_DPC_STATUS_REG_CLEAR_XBUS_DMEM_DMA 
 * @see N64_DPC_STATUS_REG_SET_XBUS_DMEM_DMA 
 * @see N64_DPC_STATUS_REG_CLEAR_FREEZE 
 * @see N64_DPC_STATUS_REG_SET_FREEZE 
 * @see N64_DPC_STATUS_REG_CLEAR_FLUSH 
 * @see N64_DPC_STATUS_REG_SET_FLUSH 
 * @see N64_DPC_STATUS_REG_CLEAR_TMEM_CTR 
 * @see N64_DPC_STATUS_REG_CLEAR_PIPE_CTR 
 * @see N64_DPC_STATUS_REG_CLEAR_CMD_CTR 
 * @see N64_DPC_STATUS_REG_CLEAR_CLOCK_CTR 
 * @see N64_DPC_STATUS_REG_XBUS_DMEM_DMA 
 * @see N64_DPC_STATUS_REG_FREEZE 
 * @see N64_DPC_STATUS_REG_FLUSH 
 * @see N64_DPC_STATUS_REG_START_GCLK 
 * @see N64_DPC_STATUS_REG_TMEM_BUSY 
 * @see N64_DPC_STATUS_REG_PIPE_BUSY 
 * @see N64_DPC_STATUS_REG_CMD_BUSY 
 * @see N64_DPC_STATUS_REG_CBUF_READY 
 * @see N64_DPC_STATUS_REG_DMA_BUSY 
 * @see N64_DPC_STATUS_REG_END_VALID 
 * @see N64_DPC_STATUS_REG_START_VALID 
 *
 */
#define N64_DPC_STATUS_REG 0x0410000C 
/** @brief Clear XBUS_DMEM_DMA bit in DPC_STATUS_REG */
#define N64_DPC_STATUS_REG_CLEAR_XBUS_DMEM_DMA 0x1
/** @brief Set XBUS_DMEM_DMA bit in DPC_STATUS_REG */
#define N64_DPC_STATUS_REG_SET_XBUS_DMEM_DMA 0x2
/** @brief Clear freeze bit in DPC_STATUS_REG */
#define N64_DPC_STATUS_REG_CLEAR_FREEZE 0x4
/** @brief Set freeze bit in DPC_STATUS_REG */
#define N64_DPC_STATUS_REG_SET_FREEZE 0x8
/** @brief Clear flush bit in DPC_STATUS_REG */
#define N64_DPC_STATUS_REG_CLEAR_FLUSH 0x10
/** @brief Set flush bit in DPC_STATUS_REG */
#define N64_DPC_STATUS_REG_SET_FLUSH 0x20
/** @brief Clear TMEM counter in DPC_STATUS_REG */
#define N64_DPC_STATUS_REG_CLEAR_TMEM_CTR 0x40
/** @brief Clear pipe counter in DPC_STATUS_REG */
#define N64_DPC_STATUS_REG_CLEAR_PIPE_CTR 0x80
/** @brief Clear command counter in DPC_STATUS_REG */
#define N64_DPC_STATUS_REG_CLEAR_CMD_CTR 0x100
/** @brief Clear clock counter in DPC_STATUS_REG */
#define N64_DPC_STATUS_REG_CLEAR_CLOCK_CTR 0x200
/** @brief XBUS_DMEM_DMA bit in DPC_STATUS_REG */
#define N64_DPC_STATUS_REG_XBUS_DMEM_DMA 0x1
/** @brief Freeze bit in DPC_STATUS_REG */
#define N64_DPC_STATUS_REG_FREEZE 0x2
/** @brief Flush bit in DPC_STATUS_REG */
#define N64_DPC_STATUS_REG_FLUSH 0x4
/** @brief Start GCLK bit in DPC_STATUS_REG */
#define N64_DPC_STATUS_REG_START_GCLK 0x8
/** @brief TMEM busy bit in DPC_STATUS_REG */
#define N64_DPC_STATUS_REG_TMEM_BUSY 0x10
/** @brief Pipe busy bit in DPC_STATUS_REG */
#define N64_DPC_STATUS_REG_PIPE_BUSY 0x20
/** @brief CMD busy bit in DPC_STATUS_REG */
#define N64_DPC_STATUS_REG_CMD_BUSY 0x40
/** @brief CBUF ready bit in DPC_STATUS_REG */
#define N64_DPC_STATUS_REG_CBUF_READY 0x80
/** @brief DMA busy bit in DPC_STATUS_REG */
#define N64_DPC_STATUS_REG_DMA_BUSY 0x100
/** @brief End valid bit in DPC_STATUS_REG */
#define N64_DPC_STATUS_REG_END_VALID 0x200
/** @brief Start valid bit in DPC_STATUS_REG */
#define N64_DPC_STATUS_REG_START_VALID 0x400

/** @brief DP clock counter */
#define N64_DPC_CLOCK_REG 0x04100010 

/** @brief DP buffer busy counter */
#define N64_DPC_BUFBUSY_REG 0x04100014 

/** @brief DP pipeline busy counter */
#define N64_DPC_PIPEBUSY_REG 0x04100018

/** @brief DP TMEM load counter */
#define N64_DPC_TMEM_REG 0x0410001C

/** @brief DP span base register */
#define N64_DPS_BASE_REG 0x04200000

/** @brief DP TMEM BIST register */
#define N64_DPS_TBIST_REG 0x04200000 

/** @brief DP span test mode */
#define N64_DPS_TEST_MODE_REG 0x04200004 

/** @brief DP span buffer test address */
#define N64_DPS_BUFTEST_ADDR_REG 0x04200008 

/** @brief DP span buffer test data */
#define N64_DPS_BUFTEST_DATA_REG 0x0420000C 

/** @brief MIPS interface base register */ 
#define N64_MI_BASE_REG 0x04300000

/** @brief MIPS init mode register */
#define N64_MI_INIT_MODE_REG 0x04300000 

/** @brief MIPS version register */
#define N64_MI_VERSION_REG 0x04300004 

/** @brief MIPS interrupts (RCP interrupts)
 *
 * To parse the contents of this register, read a u32 from this macro address and mask the following desired bits:
 * [N64_MI_INTR_REG_SP_INTR |] [N64_MI_INTR_REG_SI_INTR |] [N64_MI_INTR_REG_AI_INTR |] [N64_MI_INTR_REG_VI_INTR |][N64_MI_INTR_REG_PI_INTR |] [N64_MI_INTR_REG_DP_INTR]
 *
 */
#define N64_MI_INTR_REG 0x04300008 
/** SP Interrupt bit in N64_MI_INTR_REG */
#define N64_MI_INTR_REG_SP_INTR 0x1
/** SI Interrupt bit in N64_MI_INTR_REG */
#define N64_MI_INTR_REG_SI_INTR 0x2
/** AI Interrupt bit in N64_MI_INTR_REG */
#define N64_MI_INTR_REG_AI_INTR 0x4
/** VI Interrupt bit in N64_MI_INTR_REG */
#define N64_MI_INTR_REG_VI_INTR 0x8
/** PI Interrupt bit in N64_MI_INTR_REG */
#define N64_MI_INTR_REG_PI_INTR 0x10
/** DP Interrupt bit in N64_MI_INTR_REG */
#define N64_MI_INTR_REG_DP_INTR 0x20

/** @brief MIPS interrupt mask 
 *
 * To set this register, write a u32 to this macro address with the following value:
 * N64_MI_INTR_MASK_REG_[CLEAR/SET]_[SP/SI/AI/VI/PI/DP]
 *
 * To parse the contents of this register, read a u32 from this macro address and mask the following desired bits:
 * N64_MI_INTR_MASK_REG_[SP/SI/AI/VI/PI/DP]
 */
#define N64_MI_INTR_MASK_REG 0x0430000C
/** @brief Clear SP Interrupt mask in N64_MI_INTR_MASK_REG */
#define N64_MI_INTR_MASK_REG_CLEAR_SP_MASK 0x1
/** @brief Set SP Interrupt mask in N64_MI_INTR_MASK_REG */
#define N64_MI_INTR_MASK_REG_SET_SP_MASK 0x2
/** @brief Clear SI Interrupt mask in N64_MI_INTR_MASK_REG */
#define N64_MI_INTR_MASK_REG_CLEAR_SI_MASK 0x4
/** @brief Set SI Interrupt mask in N64_MI_INTR_MASK_REG */
#define N64_MI_INTR_MASK_REG_SET_SI_MASK 0x8
/** @brief Clear AI Interrupt mask in N64_MI_INTR_MASK_REG */
#define N64_MI_INTR_MASK_REG_CLEAR_AI_MASK 0x10
/** @brief Set AI Interrupt mask in N64_MI_INTR_MASK_REG */
#define N64_MI_INTR_MASK_REG_SET_AI_MASK 0x20
/** @brief Clear VI Interrupt mask in N64_MI_INTR_MASK_REG */
#define N64_MI_INTR_MASK_REG_CLEAR_VI_MASK 0x40
/** @brief Set VI Interrupt mask in N64_MI_INTR_MASK_REG */
#define N64_MI_INTR_MASK_REG_SET_VI_MASK 0x80
/** @brief Clear PI Interrupt mask in N64_MI_INTR_MASK_REG */
#define N64_MI_INTR_MASK_REG_CLEAR_PI_MASK 0x100
/** @brief Set PI Interrupt mask in N64_MI_INTR_MASK_REG */
#define N64_MI_INTR_MASK_REG_SET_PI_MASK 0x200
/** @brief Clear DP Interrupt mask in N64_MI_INTR_MASK_REG */
#define N64_MI_INTR_MASK_REG_CLEAR_DP_MASK 0x400
/** @brief Set DP Interrupt mask in N64_MI_INTR_MASK_REG */
#define N64_MI_INTR_MASK_REG_SET_DP_MASK 0x800
/** @brief SP Interrupt mask in N64_MI_INTR_MASK_REG */
#define N64_MI_INTR_MASK_REG_SP_MASK 0x1
/** @brief SI Interrupt mask in N64_MI_INTR_MASK_REG */
#define N64_MI_INTR_MASK_REG_SI_MASK 0x2
/** @brief AI Interrupt mask in N64_MI_INTR_MASK_REG */
#define N64_MI_INTR_MASK_REG_AI_MASK 0x4
/** @brief VI Interrupt mask in N64_MI_INTR_MASK_REG */
#define N64_MI_INTR_MASK_REG_VI_MASK 0x8
/** @brief PI Interrupt mask in N64_MI_INTR_MASK_REG */
#define N64_MI_INTR_MASK_REG_PI_MASK 0x10
/** @brief DP Interrupt mask in N64_MI_INTR_MASK_REG */
#define N64_MI_INTR_MASK_REG_DP_MASK 0x20

/** @brief VI base register */
#define N64_VI_BASE_REG 0x04400000

/** @brief VI status register 
 *
 * To set this register, write a u32 to this macro address with the following value:
 *
 * N64_VI_STATUS_REG_PIXEL_SIZE_[BLANK/5553/8888] [| N64_VI_STATUS_REG_GAMMA_DITHER_ENABLE] [| N64_VI_STATUS_REG_GAMMA_ENABLE] [| N64_VI_STATUS_REG_DIVOT_ENABLE] [| N64_VI_STATUS_REG_SERRATE] | N64_VI_STATUS_REG_AA_MODE_[AA_RESAMP_FETCH_ALWAYS/AA_MODE_AA_RESAMP/RESAMP/REPLICATE] | N64_VI_STATUS_REG_PIXEL_ADVANCE(<pixel advance>) [| N64_VI_STATUS_REG_DITHER_FILTER_ENABLE]
 *
 */
#define N64_VI_STATUS_REG 0x04400000 
/** @brief VI status register pixel size bits */
#define N64_VI_STATUS_REG_PIXEL_SIZE 0x3
/** @brief VI status register no data transfer */
#define N64_VI_STATUS_REG_PIXEL_SIZE_BLANK 0x0
/** @brief VI status register 5/5/5/3 pixel format */
#define N64_VI_STATUS_REG_PIXEL_SIZE_5553 0x2
/** @brief VI status register 8/8/8/8 pixel format  */
#define N64_VI_STATUS_REG_PIXEL_SIZE_8888 0x3
/** @brief VI status register enable gamma dither bit */
#define N64_VI_STATUS_REG_GAMMA_DITHER_ENABLE 0x4
/** @brief VI status register enable gamma boost bit */
#define N64_VI_STATUS_REG_GAMMA_ENABLE 0x8
/** @brief VI status register enable divot bit */
#define N64_VI_STATUS_REG_DIVOT_ENABLE 0x10
/** @brief VI status register unknown bit */
#define N64_VI_STATUS_REG_VBUS_CLOCK_ENABLE 0x20
/** @brief VI status register enable interlace bit */
#define N64_VI_STATUS_REG_SERRATE 0x40
/** @brief VI status register antialias mode bits */
#define N64_VI_STATUS_REG_AA_MODE 0x300
/** @brief VI status register antialias and resample (always fetch) */
#define N64_VI_STATUS_REG_AA_MODE_AA_RESAMP_FETCH_ALWAYS 0x000
/** @brief VI status register antialias and resample (fetch if necessary) */
#define N64_VI_STATUS_REG_AA_MODE_AA_RESAMP 0x100
/** @brief VI status register resample only */
#define N64_VI_STATUS_REG_AA_MODE_RESAMP 0x200
/** @brief VI status register replicate framebuffer bits */
#define N64_VI_STATUS_REG_AA_MODE_REPLICATE 0x300
/** @brief VI status register pixel advance */
#define N64_VI_STATUS_REG_PIXEL_ADVANCE 0xF000
/** @brief Convert to VI status register pixel advance */
#define N64_VI_STATUS_REG_PIXEL_ADVANCE_FMT(x) ((x & 0xf) << 12)
/** @brief VI status register enable dither filter bit */
#define N64_VI_STATUS_REG_DITHER_FILTER_ENABLE 0x10000

/** @brief VI origin register */
#define N64_VI_ORIGIN_REG 0x04400004 

/** @brief VI frame buffer width in pixels */
#define N64_VI_WIDTH_REG 0x04400008 

/** @brief VI interrupt register */
#define N64_VI_INTR_REG 0x0440000C 

/** @brief VI current line register */
#define N64_VI_CURRENT_REG 0x04400010 

/** @brief VI video timing */
#define N64_VI_BURST_REG 0x04400014 

/** @brief VI vertical sync  */
#define N64_VI_V_SYNC_REG 0x04400018 

/** @brief VI horizontal sync */
#define N64_VI_H_SYNC_REG 0x0440001C 

/** @brief VI Horizontal sync leap */
#define N64_VI_LEAP_REG 0x04400020 

/** @brief VI horizontal video */
#define N64_VI_H_START_REG 0x04400024 

/** @brief VI vertical video */
#define N64_VI_V_START_REG 0x04400028 

/** @brief VI vertical burst */
#define N64_VI_V_BURST_REG 0x0440002C 

/** @brief VI X scale */
#define N64_VI_X_SCALE_REG 0x04400030 

/** @brief VI Y scale */
#define N64_VI_Y_SCALE_REG 0x04400034

/** @brief AI base register */
#define N64_AI_BASE_REG 0x04500000

/** @brief AI buffer DRAM address */
#define N64_AI_DRAM_ADDR_REG 0x04500000 

/** @brief AI length */
#define N64_AI_LEN_REG 0x04500004 

/** @brief AI control register */
#define N64_AI_CONTROL_REG 0x04500008 

/** @brief AI status register */
#define N64_AI_STATUS_REG 0x0450000C

/** @brief AI DAC rate */
#define N64_AI_DACRATE_REG 0x04500010 

/** @brief AI bit rate */
#define N64_AI_BITRATE_REG 0x04500014

/** @brief PI base register */
#define N64_PI_BASE_REG 0x04600000

/** @brief PI DRAM address */
#define N64_PI_DRAM_ADDR_REG 0x04600000 

/** @brief PI cartridge address */
#define N64_PI_CART_ADDR_REG 0x04600004 

/** @brief PI read length */
#define N64_PI_RD_LEN_REG 0x04600008 

/** @brief PI write length */
#define N64_PI_WR_LEN_REG 0x0460000C 

/** @brief PI status register */
#define N64_PI_STATUS_REG 0x04600010 

/** @brief PI dom1 latency */
#define N64_PI_BSD_DOM1_LAT_REG 0x04600014 

/** @brief PI dom1 pulse width */
#define N64_PI_BSD_DOM1_PWD_REG 0x04600018 

/** @brief PI dom1 page size */
#define N64_PI_BSD_DOM1_PGS_REG 0x0460001C 

/** @brief PI dom1 release duration */
#define N64_PI_BSD_DOM1_RLS_REG 0x04600020 

/** @brief PI dom2 latency */
#define N64_PI_BSD_DOM2_LAT_REG 0x04600024 

/** @brief PI dom2 pulse width */
#define N64_PI_BSD_DOM2_PWD_REG 0x04600028 

/** @brief PI dom2 page size */
#define N64_PI_BSD_DOM2_PGS_REG 0x0460002C 

/** @brief PI dom1 release duration */
#define N64_PI_BSD_DOM2_RLS_REG 0x04600030

/** @brief RI base register */
#define N64_RI_BASE_REG 0x04700000

/** @brief RI mode register */
#define N64_RI_MODE_REG 0x04700000 

/** @brief RI config register */
#define N64_RI_CONFIG_REG 0x04700004 

/** @brief RI current load */
#define N64_RI_CURRENT_LOAD_REG 0x04700008 

/** @brief RI select register */
#define N64_RI_SELECT_REG 0x0470000C 

/** @brief RI refresh delay */
#define N64_RI_REFRESH_REG 0x04700010 

/** @brief RI latency */
#define N64_RI_LATENCY_REG 0x04700014 

/** @brief RI error */
#define N64_RI_RERROR_REG 0x04700018 

/** @brief RI error */
#define N64_RI_WERROR_REG 0x0470001C

/** @brief SI base register */
#define N64_SI_BASE_REG 0x04800000

/** @brief SI DRAM address */
#define N64_SI_DRAM_ADDR_REG 0x04800000 

/** @brief SI read 64 bytes */
#define N64_SI_PIF_ADDR_RD64B_REG 0x04800004 

/** @brief SI write 64 bytes */
#define N64_SI_PIF_ADDR_WR64B_REG 0x04800010 

/** @brief SI status register */
#define N64_SI_STATUS_REG 0x04800018

/** @brief PIF ROM start */
#define N64_PIF_ROM_START 0x1FC00000

/** @brief PIF ROM end */
#define N64_PIF_ROM_END 0x1FC007BF

/** @brief PIF RAM start */
#define N64_PIF_RAM_START 0x1FC007C0

/** @brief PIF RAM end */
#define N64_PIF_RAM_END 0x1FC007FC

/** @brief Cartridge domain 2 address 1 */
#define N64_CART_DOM2_ADDR1 0x05000000

/** @brief Cartridge domain 1 address 1 */
#define N64_CART_DOM1_ADDR1 0x06000000

/** @brief Cartridge domain 1 address 2 */
#define N64_CART_DOM1_ADDR2 0x10000000

#endif
