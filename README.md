

Assignment Overview

This project is a C-based program for checking assembly language instructions using an opcode table.

The program reads opcode details from opcode.txt and assembly instructions from program.asm.

A hash table is used to store and search mnemonics.

Group Members

Shinde Janhavi Pravin - 25111052
Jadhav Gayatri Bapusaheb - 25111023

GitHub Branch

Both members worked together on the same branch.

Branch Name: janhavi-gayatri-opcode

Main Work

Read opcode information from opcode.txt.
Store mnemonics using a hash table.
Read assembly instructions from program.asm.
Separate mnemonic and operands.
Check whether the mnemonic exists.
Identify the type of operands.
Display the result.
Test the program with different instructions.

Hash Table

A hash table is used to store and search instruction mnemonics.

The first character of the mnemonic is used to determine its position.

Mnemonics used include:

ADD, AND, CMP, DEC, DIV, INC, MOV, MUL, OR, SUB and XOR.

Operand Types

The program identifies the following operand types:

Register
Constant
Memory
Symbol

Examples:

EAX - Register
25 - Constant
[EAX] - Memory
VALUE - Symbol

Input Files

opcode.txt

Contains opcode details, mnemonic and operand information.

program.asm

Contains the assembly instructions to be checked.

Output

The program displays:

Line number
Mnemonic
Mnemonic status
Operand
Operand type

Files Used

assembler.c
opcode.txt
program.asm
README.md

GitHub Links

Janhavi Shinde:
https://github.com/Janhavi-2305

Gayatri Jadhav:
https://github.com/gayatrijadhav09

Project Repository:
https://github.com/gayatrijadhav09/assembly-instruction-checker

Conclusion

The project checks assembly instructions using an opcode table and hash table.

It also identifies the type of operands used in the instructions.