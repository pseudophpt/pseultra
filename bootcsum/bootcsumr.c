/*
 * pseultra/bootcsum/bootcsumr.c
 * PIFrom ipl2 checksum reverser
 *
 * (C) pseudophpt 2018
 */

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define MAGIC 0x95DACFDC

void checksum (uint32_t *bcode);
static inline uint64_t checksum_helper (uint64_t op1, uint64_t op2, uint64_t op3);

int main (int argc, char *argv[]) {
    // If arguments not adequate
    if (argc != 4) {
        printf("Usage: bootcsumr <rom file> <checksum to search for> <starting hword>\n"); 
        return 0;
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

    uint64_t checksum = strtol(argv[2], NULL, 0);
    uint16_t starthword = strtol(argv[3], NULL, 0);

    find_collision(&rom_buffer[0x10], checksum, starthword);
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
 * Try to find checksum collision 
 */ 
void find_collision (uint32_t *bcode, uint64_t desired_checksum, uint16_t starthword) {
    // Store starting hword into bootcode
    bcode[0x3ee] = (bcode[0x3ee] & 0xffff0000) | starthword;

    uint32_t preframe [16]; // Pre-calculated frame, up to what changes
    uint32_t frame [16]; // Current frame being used to test 
    uint32_t sframe [4];

    // Variables used to calculate frame 
    uint32_t *bcode_inst_ptr = bcode;
    uint32_t loop_count = 0;
    uint32_t bcode_inst = *bcode_inst_ptr;
    uint32_t next_inst;
    uint32_t prev_inst;
    
    // Calculate magic number
    uint32_t magic = MAGIC ^ bcode_inst;

    // Generate frame. This is done earlier in IPC2
    for (int i = 0; i < 16; i ++) {
        preframe[i] = magic;
    };

    // Calculate pre-frame
    for (;;) {
        /* Loop start, 11E8 - 11FC */
        prev_inst = bcode_inst;
        bcode_inst = *bcode_inst_ptr;
        loop_count ++;
        bcode_inst_ptr ++;
        next_inst = *(bcode_inst_ptr);

        /*  Main processing */
        preframe[0] += checksum_helper(0x3EF - loop_count, bcode_inst, loop_count);

        preframe[1] = checksum_helper(preframe[1], bcode_inst, loop_count);
        
        preframe[2] ^= bcode_inst;
        
        preframe[3] += checksum_helper(bcode_inst + 5, 0x6c078965, loop_count);
        
        if (prev_inst < bcode_inst) {
                preframe[9] = checksum_helper(preframe[9], bcode_inst, loop_count);
        }
        else preframe[9] += bcode_inst;
        
        preframe[4] += ((bcode_inst << (0x20 - (prev_inst & 0x1f))) | (bcode_inst >> (prev_inst & 0x1f)));
        
        preframe[7] = checksum_helper(preframe[7], ((bcode_inst >> (0x20 - (prev_inst & 0x1f))) | (bcode_inst << (prev_inst & 0x1f))), loop_count);
        
        if (bcode_inst < preframe[6]) {
            preframe[6] = (bcode_inst + loop_count) ^ (preframe[3] + preframe[6]);
        }
        else preframe[6] = (preframe[4] + bcode_inst) ^ preframe[6];

        preframe[5] += (bcode_inst >> (0x20 - (prev_inst >> 27))) | (bcode_inst << (prev_inst >> 27));

        preframe[8] = checksum_helper(preframe[8], (bcode_inst << (0x20 - (prev_inst >> 27))) | (bcode_inst >> (prev_inst >> 27)), loop_count);
        
        if (loop_count == 0x3ef) break;

        uint32_t tmp1 = checksum_helper(preframe[15], (bcode_inst >> (0x20 - (prev_inst >> 27))) | (bcode_inst << (prev_inst >> 27)), loop_count);
        preframe[15] = checksum_helper(
            tmp1,
            (next_inst << (bcode_inst >> 27)) | (next_inst >> (0x20 - (bcode_inst >> 27))),
            loop_count
        );

        uint32_t tmp2 = ((bcode_inst << (0x20 - (prev_inst & 0x1f))) | (bcode_inst >> (prev_inst & 0x1f)));
        uint32_t tmp3 = checksum_helper(preframe[14], tmp2, loop_count); // v0 at 1384
        uint32_t tmp4 = checksum_helper(tmp3, (next_inst >> (bcode_inst & 0x1f)) | (next_inst << (0x20 - (bcode_inst & 0x1f))), loop_count); // v0 at 13a4

        preframe[14] = tmp4;

        preframe[13] += ((bcode_inst >> (bcode_inst & 0x1f)) | (bcode_inst << (0x20 - (bcode_inst & 0x1f)))) + ((next_inst >> (next_inst & 0x1f)) | (next_inst << (0x20 - (next_inst & 0x1f)))); 

        preframe[10] = checksum_helper(preframe[10] + bcode_inst, next_inst, loop_count);

        preframe[11] = checksum_helper(preframe[11] ^ bcode_inst, next_inst, loop_count);

        preframe[12] += (preframe[8] ^ bcode_inst);
    }

    // Now let's try everything for the last word
    for (uint64_t word = 0;; word ++) {
        // Copy preframe over
        memcpy(&frame, &preframe, sizeof(frame));

        // Write word to end of bcode
        bcode[0x3ef] = word;

        // Restore variables
        loop_count = 0x3ee;
        bcode_inst_ptr = &bcode[0x3ee];
        bcode_inst = bcode[0x3ed];

        // Calculate frame
        // Frame calculations for 0x3ee
        prev_inst = bcode_inst;
        bcode_inst = *bcode_inst_ptr;
        loop_count ++;
        bcode_inst_ptr ++;
        next_inst = *(bcode_inst_ptr);
    
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
 
        prev_inst = bcode_inst;
        bcode_inst = *bcode_inst_ptr;
        loop_count ++;
        bcode_inst_ptr ++;
        next_inst = *(bcode_inst_ptr);
        
        // Calculations for 0x3ef
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
        

        // Second part, calculates sframe
        
        // Every value in sframe is initialized to frame[0]
        sframe[0] = frame[0];
        sframe[1] = frame[0];
        sframe[2] = frame[0];
        sframe[3] = frame[0];
    
        uint32_t *frame_word_ptr = &frame[0];
        uint32_t frame_word;

        //First calculate sframe 2 and 3, they are independent and allow for faster checking
        for (uint32_t frame_number = 0; frame_number != 0x10; frame_number ++) {
            // Updates
            frame_word = *frame_word_ptr;
    
            // Calculations   
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

        
        // If high part of checksum matches continue to calculate sframe 1 and 0
        if ((sframe[2] ^ sframe[3]) == (desired_checksum & 0xffffffff)) {
            uint32_t *frame_word_ptr = &frame[0];
            
            for (uint32_t frame_number = 0; frame_number != 0x10; frame_number ++) {
                frame_word = *frame_word_ptr;
                
                sframe[0] += ((frame_word << (0x20 - frame_word & 0x1f)) | frame_word >> (frame_word & 0x1f));
      
                if (frame_word < sframe[0]) {
                    sframe[1] += frame_word;
                }
                else {
                    sframe[1] = checksum_helper(sframe[1], frame_word, 0);
                }

                frame_word_ptr ++;
            }
            
            // Now check if it matches the checksum
            if ((checksum_helper(sframe[0], sframe[1], 0x10) & 0xffff) == (desired_checksum >> 32)) {
                printf("COLLISION FOUND! Please notify developers.\n");
                printf("Starthword: %x\n", starthword);
                printf("Word: %llx\n", word);
                
                return word;
            }
        }
        
        // End at 0xFFFFFFFF
        if (word == 0xFFFFFF) break;
    }

}
