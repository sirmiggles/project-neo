# Project NEO
Repository for the CITS3402 (High Performance Computing) Project I for 2019 relating to matrix operations.

## Install instructions

To compile the source files, simply run

```bash
make
```

or

```bash
make matrix
```

**Warnings**:

1. This program's makefile is designed specifically for Linux (`Ubuntu for Windows, v18.04 / Windows Subsystem for Linux`)
    > To compile for MacOS, alter the variable `CC` in the makefile from `gcc` to `cc`

2. Please do not move the makefile from its current directory as this will prevent the program from compiling