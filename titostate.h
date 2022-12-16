#pragma once

#include <stdint.h>

#define MACHINE_MEMSIZE 65536
#define OUTPUT_BUFFER_SIZE 16

enum register_names
{
    // General Purpose
    R0 = 0,
    R1 = 1,
    R2 = 2,
    R3 = 3,
    R4 = 4,
    R5 = 5,
    R6 = 6,
    R7 = 7,

    SP = R6,
    FP = R7,

    // Control Unit
    PC = 0,
    IR = 1,
    TR = 2, // not used for now
    SR = 3,
};

// ----- Machine State ----- //

// Registers R0 - R7
extern int32_t mach_cpu[8];

// Control unit registers
extern int32_t mach_cu[4];

// Memory of the machine
extern int32_t mach_mem[MACHINE_MEMSIZE];

int32_t mach_readmem(int32_t address);

void mach_writemem(int32_t address, int32_t value);


// Misc
extern int32_t waiting_for_input;
extern int32_t output_buffer[OUTPUT_BUFFER_SIZE];
extern int32_t output_buffer_len;