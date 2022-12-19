/*
 * machstate.c - Machine state
 * Contains definitions for memory and registers of the machine.
 */

#include "titostate.h"
#include <stdio.h>

int catastrophic_failure = 0;

// Registers R0 - R7
int32_t mach_cpu[8] = {0};

// Control unit registers
int32_t mach_pc = 0;
int32_t mach_ir = 0;
int32_t mach_tr = 0;
int32_t mach_sr = 0;

// Memory of the machine
int32_t mach_mem[MACHINE_MEMSIZE] = {0};

#ifndef CLI_MODE
int32_t waiting_for_input = 0;
int32_t output_buffer[OUTPUT_BUFFER_SIZE] = {0};
int32_t output_buffer_len = 0;
#endif

int32_t state_get_sr_bit(int idx)
{
    return (mach_sr >> idx) & 1;
}
void state_set_sr_bit(int idx, int val)
{
    if (val == 0)
        mach_sr &= ~(1 << idx);
    else if (val == 1)
        mach_sr |= (1 << idx);
    else
        printf("ERR: state_set_sr_bit: invalid value.\n");
    return;
}

// ReadMem
// Read from a memory address
int32_t mach_readmem(int32_t address)
{
    if (address < 0)
    {
        state_set_sr_bit(SR_M, 1);
        printf("ERR: Attempted to read mem out of bounds. Addr < 0\n");
        return 0;
    }
    else if (address >= MACHINE_MEMSIZE)
    {
        state_set_sr_bit(SR_M, 1);
        printf("ERR: Attempted to read mem out of bounds. Addr >= MACHINE_MEMSIZE\n");
        return 0;
    }

    return (mach_mem[address]);
}

// WriteMem
// Write to a memory address
void mach_writemem(int32_t address, int32_t value)
{
    if (address < 0)
    {
        state_set_sr_bit(SR_M, 1);
        printf("ERR: Attempted to write mem out of bounds. Addr < 0\n");
        return;
    }
    else if (address >= MACHINE_MEMSIZE)
    {
        state_set_sr_bit(SR_M, 1);
        printf("ERR: Attempted to write mem out of bounds. Addr >= MACHINE_MEMSIZE\n");
        return;
    }

    mach_mem[address] = value;
}