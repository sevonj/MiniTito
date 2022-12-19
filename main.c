#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "titomach.h"

// Defined in build script
//#define CLI_MODE // Input from and output to console
//#define VERBOSE

int main(int argc, char *argv[])
{
    // Check if the correct number of arguments was provided
    if (argc != 2)
    {
        printf("Error: Invalid number of arguments\n");
        printf("Usage: %s <filepath>\n", argv[0]);
        return 1;
    }

    // Get filepath from arguments
    const char *filepath = argv[1];

    titomach_load_prog(filepath);
    titomach_start();
    /*
    for (int i = 0; i < 287; i++)
    /*/
    while (1)
    //*/
    {
        int result = titomach_exec();

        if (result == EXE_END)
        {
            printf("Execution finished.\n");
            break;
        }
        else if (result == EXE_HALTED)
        {
            printf("Cannot continue execution. The machine is halted.\n");
            break;
        }
        else if (result == EXE_ERR)
        {
            printf("Instruction caused an error.\n");
            break;
        }
        //getchar();
    }

    return 0;
}
