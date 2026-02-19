#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEM_BYTES 100 


int main() {

    // Create a pointer to a block of memory and initialize bytes with value of 4. 
    size_t size = MEM_BYTES;
    unsigned char *u_buffer = malloc(size);
    memset(u_buffer, 4, size);

    // Prints the value of each byte in hexadecimal from user buffer. 
    for (size_t i = 0; i < size; i++) {
        printf("%02x ", *(u_buffer + i));
        if (!((i + 1) % 10)) printf("\n");
    }

    free(u_buffer);
    return 0;
}