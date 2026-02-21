#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/syscall.h>
#include <unistd.h>

#define BUFFER_SIZE 100 
#define USER_VAL 4
#define ITERATIONS 100
#define SYS_APP_HELPER 449

int main() {
 
    char *u_buffer = malloc(BUFFER_SIZE);
    struct timespec start, end; 

    // Exit if failed to allocate memory to u_buffer. 
    if (u_buffer == NULL) {
        perror("couldn't allocate memory to u_buffer");
        return 1; 
    } else {
        memset(u_buffer, USER_VAL, BUFFER_SIZE);
    }

    // Verify that all the bytes have been initialized with value from USER_VAL.
    for (size_t i = 0; i < BUFFER_SIZE; i++) {
        if (*(u_buffer + i) != USER_VAL) {
            fprintf(stderr, "failed to initialize bytes with value %d", USER_VAL);
            free(u_buffer);
            return 1;
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &start);

    for (size_t i = 0; i < ITERATIONS; i++) {
        long result = syscall(SYS_APP_HELPER, u_buffer, BUFFER_SIZE);
        if (result == -1) {
            perror("app_helper system call failed");
            free(u_buffer);
            return 1;
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
  
    // Verify that all the bytes have been initialized with value from KERNEL_VAL.
    for (size_t i = 0; i < BUFFER_SIZE; i++) {
        if (*(u_buffer + i) != 1) {
            fprintf(stderr, "failed to initialize bytes with value %d", 1);
            free(u_buffer);
            return 1;
        }
    }

    // Convert to nanoseconds first to add in the additional nanoseconds provided by timespec and then convert to microseconds. 
    double total_time_us = ((end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec)) / 1000.0;
    double avg_per_call_time_us =  total_time_us / ITERATIONS; 

    printf("app_helper called: %d\n", ITERATIONS);
    printf("Total time: %.3f us\n", total_time_us);
    printf("Average time per call: %.3f us\n", avg_per_call_time_us);

    free(u_buffer);
    return 0;
}


