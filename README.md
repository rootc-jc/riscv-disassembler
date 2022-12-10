# riscv-disassembler
## Compiling
```
$ g++ -o main src/main.cpp
```
## Running
```
$ ./main <input> <output>
```
## Input and Output format
Input file should contain HEX code line by line. \
A sample code would be: \
_0abcdefg_ \
_abcdefg0_ \
Output will be standard _.s_ file