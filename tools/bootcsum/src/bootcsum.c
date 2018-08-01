/*
 * pseultra/tools/bootcsum/src/bootcsum.c
 * PIFrom ipl2 checksum function decomp
 *
 * (C) pseudophpt 2018
 */

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define MAGIC 0x95DACFDC

uint64_t calculate_checksum (uint32_t *bcode);
static inline uint64_t checksum_helper (uint64_t op1, uint64_t op2, uint64_t op3);

int main (int argc, char *argv[]) {
    // If arguments not adequate
    if (argc < 2) {
        printf("Usage: bootcsum <rom file> [<expected checksum>]\n"); 
        return -1;
    }
    
    FILE* rom_file;

    uint32_t rom_buffer[0x1000 / sizeof(uint32_t)];
    rom_file = fopen(argv[1], "r");
    fread(rom_buffer, sizeof(uint32_t), 0x1000 / sizeof(uint32_t), rom_file);
    fclose(rom_file); 

    // LE to BE
    for (int i = 0; i < 0x1000 / sizeof(uint32_t); i++) {
        uint32_t le = rom_buffer[i];
        uint32_t be = ((le & 0xff) << 24) | ((le & 0xff00) << 8) | ((le & 0xff0000) >> 8) | ((le & 0xff000000) >> 24);
        rom_buffer[i]  = be;
    }

    // Verification or calculation
    if (argc == 2) {
        // Calculation
        uint64_t checksum = calculate_checksum(&rom_buffer[0x10]);

        printf("0x%llx\n", checksum);
        return 0;
    }
    
    if (argc == 3) {
        // Verification
        uint64_t expected_checksum = strtol(argv[2], NULL, 0);
        uint64_t checksum = calculate_checksum(&rom_buffer[0x10]); 
       
        if (checksum == expected_checksum) {
            printf("Correct\n");
            return 0;
        }
        else {
            printf("Incorrect:\n");
            printf("Expected 0x%llx, got 0x%llx\n", expected_checksum, checksum);
            return -1;
        }
    }
} 

/*
 * Helper function commonly called during checksum
 */
static inline uint64_t checksum_helper (uint64_t op1, uint64_t op2, uint64_t op3) {
    int high_mult;
    int low_mult;

    if (op2 == 0) {
        op2 = op3;
    }

    low_mult = (op1 * op2) & 0x00000000FFFFFFFF; 
    high_mult = ((op1 * op2) & 0xFFFFFFFF00000000) >> 32; 

    if (high_mult - low_mult == 0) {
        return low_mult;
    }

    else return high_mult - low_mult;
}

/*
 * Decompiled checksum function 
 */ 
uint64_t calculate_checksum (uint32_t *bcode) {
    uint32_t *bcode_inst_ptr = bcode;
    uint32_t loop_count = 0;
    uint32_t bcode_inst = *bcode_inst_ptr;
    uint32_t next_inst;
    uint32_t prev_inst;

    uint32_t frame [16];
    uint32_t sframe [4];

    // Calculate magic number
    uint32_t magic = MAGIC ^ bcode_inst;

    // Generate frame. This is done earlier in IPC2
    for (int i = 0; i < 16; i ++) {
        frame[i] = magic;
    };

    // First part of checksum, calculates frame
    for (;;) {
        /* Loop start, 11E8 - 11FC */
        prev_inst = bcode_inst;
        bcode_inst = *bcode_inst_ptr;
        loop_count ++;
        bcode_inst_ptr ++;
        next_inst = *(bcode_inst_ptr);

        /*  Main processing */
        frame[0] += checksum_helper(0x3EF - loop_count, bcode_inst, loop_count);

        frame[1] = checksum_helper(frame[1], bcode_inst, loop_count);
       
        frame[2] ^= bcode_inst;
        
        frame[3] += checksum_helper(bcode_inst + 5, 0x6c078965, loop_count);
        
        if (prev_inst < bcode_inst) {
                frame[9] = checksum_helper(frame[9], bcode_inst, loop_count);
        }
        else frame[9] += bcode_inst;
        
        frame[4] += ((bcode_inst << (0x20 - (prev_inst & 0x1f))) | (bcode_inst >> (prev_inst & 0x1f)));
        
        frame[7] = checksum_helper(frame[7], ((bcode_inst >> (0x20 - (prev_inst & 0x1f))) | (bcode_inst << (prev_inst & 0x1f))), loop_count);
        
        if (bcode_inst < frame[6]) {
            frame[6] = (bcode_inst + loop_count) ^ (frame[3] + frame[6]);
        }
        else frame[6] = (frame[4] + bcode_inst) ^ frame[6];

        frame[5] += (bcode_inst >> (0x20 - (prev_inst >> 27))) | (bcode_inst << (prev_inst >> 27));

        frame[8] = checksum_helper(frame[8], (bcode_inst << (0x20 - (prev_inst >> 27))) | (bcode_inst >> (prev_inst >> 27)), loop_count);
        
        if (loop_count == 0x3F0) break;

        uint32_t tmp1 = checksum_helper(frame[15], (bcode_inst >> (0x20 - (prev_inst >> 27))) | (bcode_inst << (prev_inst >> 27)), loop_count);
        frame[15] = checksum_helper(
            tmp1,
            (next_inst << (bcode_inst >> 27)) | (next_inst >> (0x20 - (bcode_inst >> 27))),
            loop_count
        );

        uint32_t tmp2 = ((bcode_inst << (0x20 - (prev_inst & 0x1f))) | (bcode_inst >> (prev_inst & 0x1f)));
        uint32_t tmp3 = checksum_helper(frame[14], tmp2, loop_count); // v0 at 1384
        uint32_t tmp4 = checksum_helper(tmp3, (next_inst >> (bcode_inst & 0x1f)) | (next_inst << (0x20 - (bcode_inst & 0x1f))), loop_count); // v0 at 13a4

        frame[14] = tmp4;

        frame[13] += ((bcode_inst >> (bcode_inst & 0x1f)) | (bcode_inst << (0x20 - (bcode_inst & 0x1f)))) + ((next_inst >> (next_inst & 0x1f)) | (next_inst << (0x20 - (next_inst & 0x1f)))); 

        frame[10] = checksum_helper(frame[10] + bcode_inst, next_inst, loop_count);

        frame[11] = checksum_helper(frame[11] ^ bcode_inst, next_inst, loop_count);

        frame[12] += (frame[8] ^ bcode_inst);
    }

    // Second part, calculates sframe
    
    // Every value in sframe is initialized to frame[0]
    for (int i = 0; i < 4; i ++) {
        sframe[i] = frame[0];
    }

    uint32_t *frame_word_ptr = &frame[0];
    uint32_t frame_word;
    
    for (uint32_t frame_number = 0; frame_number != 0x10; frame_number ++) {
        // Updates
        frame_word = *frame_word_ptr;

        // Calculations
        sframe[0] += ((frame_word << (0x20 - frame_word & 0x1f)) | frame_word >> (frame_word & 0x1f));

        if (frame_word < sframe[0]) {
            sframe[1] += frame_word;
        }
        else {
            sframe[1] = checksum_helper(sframe[1], frame_word, 0);
        }

        if (((frame_word & 0x02) >> 1) == (frame_word & 0x01)) {
            sframe[2] += frame_word;
        }
        else {
            sframe[2] = checksum_helper(sframe[2], frame_word, frame_number);
        }

        if (frame_word & 0x01 == 1) {
            sframe[3] ^= frame_word;
        }
        else {
            sframe[3] = checksum_helper(sframe[3], frame_word, frame_number);
        }

        frame_word_ptr ++;
    }

    // combine sframe into checksum
    uint64_t checksum = sframe[2] ^ sframe[3]; 
    checksum |= checksum_helper(sframe[0], sframe[1], 0x10) << 32;
    checksum &= 0x0000ffffffffffff;

    return checksum;
}
