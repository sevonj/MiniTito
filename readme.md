
# Titolib
A hastily made ttk-91 emulator.

Because [this](https://gist.github.com/sevonj/9e10a2ff824b5348ae5d32048b7fb38d) was too much for the original TitoKone.
See (TitoMachine)[https://github.com/sevonj/titomachine] for a gui implementation.

### Notes:
- Command line only (for now).
- You need to compile the files with titokone.
- Instructions may and probably will fail silently.
- Only working syscall is =halt.
- Bit operations are not implemented: AND, OR, XOR, SHL, SHR, NOT, SHRA.

### Usage
        $ titomachine /path/to/compiled_file.b91

### Source structure / explanations

        +------------------------+
        | main.c                 |
        | Just a front that      |
        | calls the real titolib |
        +------------------------+
                    | #include titomachine.h
                    V
        +----------------------------+
        | titomachine.c              |
        | Main will call funcs here, |
        | such as                    |
        | - Load program             |
        | - Clear mem                |
        | - Execute instruction      |
        +----------------------------+
                    |            | #include titoinstr.h
                    |            V
                    |      +---------------------------------------+
                    |      | titoinstr.c                           |
                    |      | Instruction code.                     |
                    |      | titomachine.c will call exec_instr(). |
                    |      +---------------------------------------+
                    |            | #include titostate.h
                    V            V
        +------------------------------------+
        | titostate.c                        |
        | Machine state.                     |
        | Definitions for mem and registers. |
        | Funcs to safely r/w mem            |
        +------------------------------------+
