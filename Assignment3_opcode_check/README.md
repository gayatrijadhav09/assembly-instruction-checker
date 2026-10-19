Opcode Check Assignment

1] Assignment Overview

The Opcode Check Project is a C-based program designed to read and check assembly language instructions using an opcode table.

The program reads opcode information from "opcode.txt" and assembly instructions from "program.asm".

A hash table is used to store and search the instruction mnemonics. The program also identifies the type of operands used in the assembly instructions.

The project was developed and tested together by both group members.


2] Team Members and Responsibilities

1. Shinde Janhavi Pravin — Opcode and Hash Table Handling

Responsibilities:

Reads the opcode information from "opcode.txt".

Stores instruction mnemonics in the hash table.

Searches for the mnemonic in the hash table.

Checks whether the given mnemonic is present or not.

Helped in testing the program.

GitHub:
https://github.com/Janhavi-2305


2. Jadhav Gayatri Bapusaheb — Assembly and Operand Handling

Responsibilities:

Reads the assembly instructions from "program.asm".

Separates the mnemonic and operands.

Identifies the type of operands.

Displays the result of the instruction checking.

Helped in testing and correcting the program.

GitHub:
https://github.com/gayatrijadhav09


Both members worked together on the final C program and testing.


3] GitHub Branch

Both members worked on the same branch.

Branch:
"janhavi-gayatri-opcode"

The branch contains the project files and the final program developed by both members.


4] Program Execution Flow

The overall flow of the program is:

opcode.txt
      ↓
Hash Table
      ↓
program.asm
      ↓
Read Mnemonic and Operands
      ↓
Search Mnemonic
      ↓
Identify Operand Type
      ↓
Final Output

The program first reads the opcode table and stores the mnemonics in a hash table.

The assembly program is then read line by line. The mnemonic is separated from the operands and searched in the hash table.

The program also identifies whether an operand is a Register, Constant, Memory or Symbol.

Finally, the result is displayed on the screen.


5] Input Files

The project uses the following input files:

"program.asm" — Contains the assembly language instructions that need to be checked.

"opcode.txt" — Contains the opcode table used to find and verify instruction mnemonics.


6] Program Files

The project contains the following files:

"assembler.c" — Main C program containing the hash table, mnemonic searching and operand checking.

"opcode.txt" — Opcode information file.

"program.asm" — Assembly instruction input file.

"README.md" — Project documentation.


7] GitHub Repository

Repository:
https://github.com/gayatrijadhav09/assembly-instruction-checker


8] Conclusion

The project demonstrates the use of a hash table for storing and searching assembly instruction mnemonics.

It also checks the operands used in the instructions and identifies their types.

Both group members contributed to the development, testing and final implementation of the project.