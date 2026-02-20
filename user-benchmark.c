#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BYTES 100 
#define USER_VAL 4
#define KERNEL_VAL 1
#define ITERATIONS 500
#define SYS_APP_HELPER 449

int main() {

    // Create a pointer to a block of memory and initialize bytes with value of 4. 
    unsigned char *u_buffer = malloc(BYTES);
    memset(u_buffer, USER_VAL, BYTES);

    // Verify that all the bytes have been initialized with value from USER_VAL.
    for (size_t i = 0; i < BYTES; i++) {
        if (*(u_buffer + i) != USER_VAL) {
            fprintf(stderr, "Failed to initialize bytes with value %d", USER_VAL);
            return 1;
        }
    }

    // insert system call here... (make sure to pass Kernel value into sys call)
    // make a for loop that calls the system call a certain amount of times.
    // for (size_t i = 0; i < ITERATIONS; i++) {

    // }


    // Verify that all the bytes have been initialized with value from KERNEL_VAL.
    // for (size_t i = 0; i < BYTES; i++) {
    //     if (*(u_buffer + i) != KERNEL_VAL) {
    //         fprintf(stderr, "Failed to initialize bytes with value %d", KERNEL_VAL);
    //         return 1;
    //     }
    // }

    free(u_buffer);
    return 0;
}


