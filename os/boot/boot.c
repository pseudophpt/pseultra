/*
 * pseultra/os/boot/boot_s.s
 * OS boot code
 * 
 * (C) pseudophpt 2018 
 */

#include <n64.h>

extern void __osInitExceptions (void);
extern void main (void);

void __osBoot () {
    /* Initialize exceptions */
    __osInitExceptions();

    /* Call main process */
    main();
}


