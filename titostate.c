/*
 * machstate.c - Machine state
 * Contains definitions for memory and registers of the machine.
 */

#include "titostate.h"
#include <stdio.h>

// Registers R0 - R7
int32_t mach_cpu[8] = {0};

// Control unit registers
int32_t mach_cu[4] = {0};

// Memory of the machine
int32_t mach_mem[MACHINE_MEMSIZE] = {0};

int32_t waiting_for_input = 0;

int32_t output_buffer[OUTPUT_BUFFER_SIZE] = {0};
int32_t output_buffer_len = 0;

// ReadMem
// Read from a memory address
int32_t mach_readmem(int32_t address){
    if (address < 0)
    {
        printf("ERR: Attempted to read mem out of bounds. Addr < 0\n");
        return (0);
    }
    else if (address >= MACHINE_MEMSIZE)
    {
        printf("ERR: Attempted to read mem out of bounds. Addr >= MACHINE_MEMSIZE\n");
        return (0);
    }

    return(mach_mem[address]);
}

// WriteMem
// Write to a memory address
void mach_writemem(int32_t address, int32_t value){
    if (address < 0)
    {
        printf("ERR: Attempted to write mem out of bounds. Addr < 0\n");
        return;
    }
    else if (address >= MACHINE_MEMSIZE)
    {
        printf("ERR: Attempted to write mem out of bounds. Addr >= MACHINE_MEMSIZE\n");
        return;
    }

    mach_mem[address] = value;
}