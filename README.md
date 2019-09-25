# Project NEO
Repository for the CITS3402 (High Performance Computing) Project I for 2019 relating to matrix operations.

## Compiling the Source

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

## Running the program

To execute the program, simply run `matrix` from its current directory in the command line:

```
./matrix <op> (<op_arg>) -f <file_1> (<file_2>) (<optional_flags>)
```

**NOTE**: 

If program is executed with the `-t` tag omitted, the program will execute in *single-thread* mode as default with no multi-threading, i.e. `num_threads = 1`.

Including this tag and the associated number of threads, the program will then execute in *parallel* mode

### Execution Flags

```
-f  <file_1> (<file_2>)     = load the files necessary, file_2 is only needed for two matrix operations
-t  <num_threads>           = set the number of threads to num_threads, num_threads >= 1
-l                          = indicator flag of if a log produced
```

### Matrix Operations

```
Single Matrix:
-sm /%f     =   scalar multiplication, by scalar factor f
-tr         =   trace
-ts         =   transpose

Two Matrix:
-ad     =   matrix addition of file_1 and file_2
-mm     =   matrix multiplication --> file_1 x file_2
