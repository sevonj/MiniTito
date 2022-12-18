#include "titomach.h"

int prog_size = 0;
int data_size = 0;

// --------------------------------------------------------------------------------------------- //
// ----- Control Funcs ----- //

void titomach_stop()
{
    mach_cu[PC] = -1;
    waiting_for_input = 0;
}
void titomach_start()
{
    titomach_stop();
    mach_cu[PC] = 0;
    mach_cpu[SP] = prog_size + data_size;
    mach_cpu[FP] = prog_size + data_size;
    printf("Init SP: %d\n", mach_cpu[SP]);
}
void titomach_clear_mem()
{
    titomach_stop();
    mach_cpu[SP] = 0;
    mach_cpu[FP] = 0;
    memset(mach_mem, 0, sizeof(mach_mem));
    prog_size = 0;
    data_size = 0;
    output_buffer_len = 0;
}
// Load a .b91 file into memory
void titomach_load_prog(const char *filename)
{
    titomach_stop();
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error: Unable to open file '%s' for reading\n", filename);
        return;
    }

    char line[32];
    // size of executable area. unused.

    int i = 0;

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        // printf("%s", line);
        if (strncmp(line, "___b91___\n", 20) == 0)
            continue;

        if (strncmp(line, "___code___\n", 20) == 0)
        {
            fgets(line, sizeof(line), fp);

            int a, b; // first & last address
            sscanf(line, "%d %d", &a, &b);
            prog_size = b + 1;
            continue;
        }

        if (strncmp(line, "___data___\n", 20) == 0)
        {
            fgets(line, sizeof(line), fp);
            int a, b; // first & last address
            sscanf(line, "%d %d", &a, &b);
            data_size = b - a;
            continue;
        }

        if (strncmp(line, "___symboltable___\n", 20) == 0)
            return; // we don't care about symbol table yet

        if (strncmp(line, "___end___\n", 20) == 0)
            return;

        if (i >= MACHINE_MEMSIZE)
            return;

        sscanf(line, "%d", &mach_mem[i]);
        i++;
    }

    fclose(fp);
}

int titomach_exec()
{
    if (waiting_for_input)
        return EXE_WAIT;
    if (mach_cu[PC] < 0)
    {
        printf("titomach_exec: called but the machine is halted.");
        return EXE_HALTED;
    }

    // Load instruction
    mach_cu[IR] = mach_mem[mach_cu[PC]];

    // print_instr();
    exec_instr();

    if (mach_cu[PC] < 0)
        return EXE_END;

    return EXE_OK;
    return EXE_ERR; // No invalid instruction / other error check yet.
}

#ifndef CLI_MODE
int32_t titomach_is_waiting_for_input()
{
    return waiting_for_input;
}
void titomach_input(int32_t n)
{
    input(n);
}

int32_t titomach_output_len(){
    return output_buffer_len;
}
int32_t titomach_output(int32_t idx){
    return output_buffer[idx];
}
#endif
// debug

int32_t titomach_debug_read_mem(int address)
{
    return mach_readmem(address);
}
// void titomach_debug_write_mem(int address, int value){};

int32_t titomach_debug_read_reg(int idx)
{
    if (idx < 0)
    {
        printf("titomach_debug_read_reg: Attempted to read cpu register index < 0.");
        return -6969; // This should make it clear enough that something is wrong. Good for now.
    }
    else if (idx > 7)
    {
        printf("titomach_debug_read_reg: Attempted to read cpu register index > 7.");
        return 6969;
    }
    return mach_cpu[idx];
}
// void titomach_debug_write_reg(int idx, int value){};
int32_t titomach_debug_read_cureg(int idx)
{
    if (idx < 0)
    {
        printf("titomach_debug_read_cureg: Attempted to read cpu register index < 0.");
        return -6969; // This should make it clear enough that something is wrong. Good for now.
    }
    else if (idx > 3)
    {
        printf("titomach_debug_read_cureg: Attempted to read cpu register index > 3.");
        return 6969;
    }
    return mach_cu[idx];
}