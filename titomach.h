#pragma once

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "titoinstr.h"
#include "titostate.h"

enum titomach_exec_return{
    EXE_HALTED = -1,
    EXE_OK = 0,
    EXE_END = 1,
    EXE_ERR = 2,
};

// --------------------------------------------------------------------------------------------- //
// ----- Control functions ----- //
void titomach_clear_mem();

void titomach_load_prog(const char *filename);

void titomach_start();

int titomach_exec();

// ----- Debug  functions ----- //
int32_t titomach_debug_read_mem(int address);

void titomach_debug_write_mem(int address, int value);