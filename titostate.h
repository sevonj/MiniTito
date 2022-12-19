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
enum sr_bits
{
    SR_G = 31, // Comp Greater
    SR_E = 30, // Comp Equal
    SR_L = 29, // Comp Less

    SR_O = 28, // Overflow
    SR_Z = 27, // Zero division
    SR_U = 26, // Unknown instruction
    SR_M = 25, // Forbidden mem address

    SR_I = 24, // Device Interrupt
    SR_S = 23, // SVC
    SR_P = 22, // Privileged mode
    SR_D = 21, // Disable Interrupts
};

// ----- Machine State ----- //
extern int catastrophic_failure;

// Registers R0 - R7
extern int32_t mach_cpu[8];

// Control unit registers
extern int32_t mach_cu[4];

// Memory of the machine
extern int32_t mach_mem[MACHINE_MEMSIZE];

int32_t state_get_sr_bit(int idx);
void state_set_sr_bit(int idx, int val);

int32_t mach_readmem(int32_t address);
void mach_writemem(int32_t address, int32_t value);

// Misc
extern int32_t waiting_for_input;
extern int32_t output_buffer[OUTPUT_BUFFER_SIZE];
extern int32_t output_buffer_len;