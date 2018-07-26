/*
 * pseultra/headers/n64.h
 * N64 definitions for C
 * 
 * (C) pseudophpt 2018
 */

#ifndef N64_H_GUARD
#define N64_H_GUARD

#include <stdint.h>

/* 
 * ROM Header Format
 */

#define PI_VALUES 0x80371240

typedef struct __attribute__((__packed__)) rom_header_t {
    uint32_t pi_regs;
    uint32_t clock_rate;
    uint32_t boot_address;
    uint32_t release;
    uint32_t rom_start;
    uint32_t rom_length;
    uint32_t padding [2];
    char image_name [0x14];
    uint8_t padding2 [7];
    uint8_t manufacturer_id;
    uint16_t cart_id;
    uint8_t country;
    uint8_t padding3;
} rom_header;

/*
 * Exception codes
 */

#define EXCEPTION_INT 0
#define EXCEPTION_MOD 1
#define EXCEPTION_TLBL 2
#define EXCEPTION_TLBS 3
#define EXCEPTION_ADEL 4
#define EXCEPTION_ADES 5
#define EXCEPTION_IBE 6
#define EXCEPTION_DBE 7
#define EXCEPTION_SYS 8
#define EXCEPTION_BP 9
#define EXCEPTION_RI 10
#define EXCEPTION_CPU 11
#define EXCEPTION_OV 12
#define EXCEPTION_TR 13

#define EXCEPTION_FPE 15

#define EXCEPTION_WATCH 23

/*
 * Exception vectors
 */

#define EXC_VEC_NMI 0xBFC00000
#define EXC_VEC_TLB_MISS 0x80000000
#define EXC_VEC_XTLB_MISS 0x80000080
#define EXC_VEC_GENERAL 0x80000180

/*
 * Interrupt causes
 */

#define INT_CAUSE_SW1 0
#define INT_CAUSE_SW2 1
#define INT_CAUSE_RCP 2
#define INT_CAUSE_CART 3
#define INT_CAUSE_PRENMI 4
#define INT_CAUSE_RDBR 5
#define INT_CAUSE_RDBW 6
#define INT_CAUSE_TIMER 7

#define INT_CAUSE_BIT_SW1 (2 << (INT_CAUSE_SW1 + 8))
#define INT_CAUSE_BIT_SW2 (2 << (INT_CAUSE_SW2 + 8))
#define INT_CAUSE_BIT_RCP (2 << (INT_CAUSE_RCP + 8))
#define INT_CAUSE_BIT_CART (2 << (INT_CAUSE_CART + 8))
#define INT_CAUSE_BIT_PRENMI (2 << (INT_CAUSE_PRENMI + 8))
#define INT_CAUSE_BIT_RDBR (2 << (INT_CAUSE_RDBR + 8))
#define INT_CAUSE_BIT_RDBW (2 << (INT_CAUSE_RDBW + 8))
#define INT_CAUSE_BIT_TIMER (2 << (INT_CAUSE_TIMER + 8))

/*
 * Memory segments
 */

#define KUSEG 0x00000000
#define KSEG0 0x80000000
#define KSEG1 0xA0000000
#define KSSEG 0xC0000000
#define KSEG3 0xE0000000

/* 
 * RDRAM Registers
 */

#define RDRAM_BASE_REG 0x03F00000

#define RDRAM_CONFIG_REG 0x03F00000 
#define RDRAM_DEVICE_TYPE_REG 0x03F00000 
#define RDRAM_DEVICE_ID_REG 0x03F00004
#define RDRAM_DELAY_REG 0x03F00008 
#define RDRAM_MODE_REG 0x03F0000C 
#define RDRAM_REF_INTERVAL_REG 0x03F00010 
#define RDRAM_REF_ROW_REG 0x03F00014 
#define RDRAM_RAS_INTERVAL_REG 0x03F00018 
#define RDRAM_MIN_INTERVAL_REG 0x03F0001C 
#define RDRAM_ADDR_SELECT_REG 0x03F00020 
#define RDRAM_DEVICE_MANUF_REG 0x03F00024 

/*
 * SP Registers
 */

#define SP_BASE_REG 0x04040000

#define SP_DMEM 0x04000000 
#define SP_IMEM 0x04001000 
#define SP_MEM_ADDR_REG 0x04040000 
#define SP_DRAM_ADDR_REG 0x04040004 
#define SP_RD_LEN_REG 0x04040008 
#define SP_WR_LEN_REG 0x0404000C 
#define SP_STATUS_REG 0x04040010 
#define SP_DMA_FULL_REG 0x04040014 
#define SP_DMA_BUSY_REG 0x04040018 
#define SP_SEMAPHORE_REG 0x0404001C 
#define SP_PC_REG 0x04080000 
#define SP_IBIST_REG 0x04080004

/* 
 * DP Command Registers
 */

#define DPC_BASE_REG 0x04100000

#define DPC_START_REG 0x04100000 
#define DPC_END_REG 0x04100004 
#define DPC_CURRENT_REG 0x04100008 
#define DPC_STATUS_REG 0x0410000C 
#define DPC_CLOCK_REG 0x04100010 
#define DPC_BUFBUSY_REG 0x04100014 
#define DPC_PIPEBUSY_REG 0x04100018
#define DPC_TMEM_REG 0x0410001C

/*
 * DP Span Registers
 */

#define DPS_BASE_REG 0x04200000

#define DPS_TBIST_REG 0x04200000 
#define DPS_TEST_MODE_REG 0x04200004 
#define DPS_BUFTEST_ADDR_REG 0x04200008 
#define DPS_BUFTEST_DATA_REG 0x0420000C 

/*
 * MIPS Interface Registers
 */

#define MI_BASE_REG 0x04300000

#define MI_INIT_MODE_REG 0x04300000 
#define MI_VERSION_REG 0x04300004 
#define MI_INTR_REG 0x04300008 
#define MI_INTR_MASK_REG 0x0430000C

/*
 * VI Registers
 */

#define VI_BASE_REG 0x04400000

#define VI_STATUS_REG 0x04400000 
#define VI_ORIGIN_REG 0x04400004 
#define VI_WIDTH_REG 0x04400008 
#define VI_INTR_REG 0x0440000C 
#define VI_CURRENT_REG 0x04400010 
#define VI_BURST_REG 0x04400014 
#define VI_V_SYNC_REG 0x04400018 
#define VI_H_SYNC_REG 0x0440001C 
#define VI_LEAP_REG 0x04400020 
#define VI_H_START_REG 0x04400024 
#define VI_V_START_REG 0x04400028 
#define VI_V_BURST_REG 0x0440002C 
#define VI_X_SCALE_REG 0x04400030 
#define VI_Y_SCALE_REG 0x04400034

/*
 * AI Registers
 */

#define AI_BASE_REG 0x04500000

#define AI_DRAM_ADDR_REG 0x04500000 
#define AI_LEN_REG 0x04500004 
#define AI_CONTROL_REG 0x04500008 
#define AI_STATUS_REG 0x0450000C 
#define AI_DACRATE_REG 0x04500010 
#define AI_BITRATE_REG 0x04500014

/*
 * PI Registers
 */

#define PI_BASE_REG 0x04600000

#define PI_DRAM_ADDR_REG 0x04600000 
#define PI_CART_ADDR_REG 0x04600004 
#define PI_RD_LEN_REG 0x04600008 
#define PI_WR_LEN_REG 0x0460000C 
#define PI_STATUS_REG 0x04600010 
#define PI_BSD_DOM1_LAT_REG 0x04600014 
#define PI_BSD_DOM1_PWD_REG 0x04600018 
#define PI_BSD_DOM1_PGS_REG 0x0460001C 
#define PI_BSD_DOM1_RLS_REG 0x04600020 
#define PI_BSD_DOM2_LAT_REG 0x04600024 
#define PI_BSD_DOM2_PWD_REG 0x04600028 
#define PI_BSD_DOM2_PGS_REG 0x0460002C 
#define PI_BSD_DOM2_RLS_REG 0x04600030

/*
 * RI Registers
 */

#define RI_BASE_REG 0x04700000

#define RI_MODE_REG 0x04700000 
#define RI_CONFIG_REG 0x04700004 
#define RI_CURRENT_LOAD_REG 0x04700008 
#define RI_SELECT_REG 0x0470000C 
#define RI_REFRESH_REG 0x04700010 
#define RI_LATENCY_REG 0x04700014 
#define RI_RERROR_REG 0x04700018 
#define RI_WERROR_REG 0x0470001C

/*
 * SI Registers
 */

#define SI_BASE_REG 0x04800000

#define SI_DRAM_ADDR_REG 0x04800000 
#define SI_PIF_ADDR_RD64B_REG 0x04800004 
#define SI_PIF_ADDR_WR64B_REG 0x04800010 
#define SI_STATUS_REG 0x04800018

/*
 * PIF ROM
 */

#define PIF_ROM_START 0x1FC00000
#define PIF_ROM_END 0x1FC007BF

/*
 * PIF RAM
 */

#define PIF_RAM_START 0x1FC007C0
#define PIF_RAM_END 0x1FC007FC

/*
 * Cartridge domains
 */

#define CART_DOM2_ADDR1 0x05000000
#define CART_DOM1_ADDR1 0x06000000
#define CART_DOM1_ADDR2 0x10000000

#endif
