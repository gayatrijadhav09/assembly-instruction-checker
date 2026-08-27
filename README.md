# Assembly Instruction Checker
 1. About the Project

This project is written in C language to check assembly language instructions.

The program reads opcode information from one file and assembly instructions from another file. It checks whether the mnemonic is available and identifies the type of operands used.

## 2. Group Members

1. Shinde Janhavi Pravin - 25111052
2. Jadhav Gayatri Bapusaheb - 25111023

## 3. Work Distribution

Both members worked together on the program.

- Wrote the C program together.
- Created the hash table for storing mnemonics.
- Read opcode information from opcode.txt.
- Read assembly instructions from program.asm.
- Implemented mnemonic searching.
- Implemented operand type checking.
- Tested the program with different inputs.
- Checked and corrected the output.

## 4. Program Working

The program works in the following way:

1. It reads the opcode information from opcode.txt.
2. The mnemonics are stored in a hash table.
3. It reads the assembly instructions from program.asm.
4. It separates the mnemonic and operands.
5. It searches for the mnemonic in the hash table.
6. It identifies the operand type.
7. It displays the result.

## 5. Hash Table

A hash table is used to store and search the instruction mnemonics.

The first character of the mnemonic is used to find its position in the hash table.

Example:

ADD
AND
CMP
DEC
DIV
INC
MOV
MUL
OR
SUB
XOR

## 6. Operand Types

The program identifies the following operand types:

EAX       - Register

25        - Constant

[EAX]     - Memory

VALUE     - Symbol

## 7. Input Files

### opcode.txt

This file contains opcode, mnemonic and operand information.

Example:

05 id        ADD   2   EAX     imm32   NO    -1    NO
81 /0 id     ADD   2   r/m32   imm32   YES   000   NO
01 /r        ADD   2   r/m32   r32     YES   REG   NO
03 /r        ADD   2   r32     r/m32   YES   REG   NO

### program.asm

This file contains the assembly instructions to be checked.

Example:

SUB ECX, EAX
AND EDX, 25
OR EAX, ECX
XOR EBX, 15
MOV EDX, [EAX]
INC EBX
DEC EDX
MUL ECX
DIV EAX
ABC EAX, EBX

## 8. Output

The program displays:

- Line number
- Mnemonic
- Whether the mnemonic exists
- Operand used
- Type of operand

Example:

Line : 1
Mnemonic : SUB
Exists : YES
Operand 1 : ECX
Type : Register
Operand 2 : EAX
Type : Register

For an unknown mnemonic:

Line : 10
Mnemonic : ABC
Exists : NO
Operand 1 : EAX
Type : Register
Operand 2 : EBX
Type : Register

## 9. Files Used

assembler.c
opcode.txt
program.asm
README.md

## 10. Conclusion

This project checks assembly language instructions using an opcode table and a hash table. It also identifies the type of operands used in the assembly program.