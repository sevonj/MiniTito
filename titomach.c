#include "titomach.h"

int prog_size = 0;
int data_size = 0;

// --------------------------------------------------------------------------------------------- //
// ----- Control Funcs ----- //

void titomach_clear_mem()
{
    memset(mach_mem, 0, sizeof(mach_mem));
}

// Load a .b91 file into memory
void titomach_load_prog(const char *filename)
{
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

void titomach_start()
{
    mach_cu[PC] = 0;
    mach_cpu[SP] = prog_size + data_size -1;
    mach_cpu[FP] = prog_size + data_size -1;
    printf("Init SP: %d\n", mach_cpu[SP]);
}

int titomach_exec()
{
    if (mach_cu[PC] < 0)
    {
        printf("titomach_exec: called but the machine is halted.");
        return (EXE_HALTED);
    }

    // Load instruction
    mach_cu[IR] = mach_mem[mach_cu[PC]];

    //print_instr();
    exec_instr();

    if (mach_cu[PC] < 0)
        return (EXE_END);
        
    return (EXE_OK);
    return (EXE_ERR); // No invalid instruction / other error check yet.
}