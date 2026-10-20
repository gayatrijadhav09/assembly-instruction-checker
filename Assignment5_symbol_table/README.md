
# Symbol Table Assignment - 5

This is a C program that generates a symbol table from an assembly language program.

It reads assembly instructions and data declarations, identifies symbols, calculates their sizes and addresses, and displays the symbol table. The program uses an opcode file to identify supported instructions.

## Steps
- Read an assembly language program from `assembly.asm`.
- Read instruction details from `opcode.txt`.
- Identify symbols and labels.
- Calculate the size and address of each symbol.
- Display the symbol table in a tabular format.
- Identify undefined symbols and display error messages.

## Files
- `symbol_table.c` - C source code.
- `assembly.asm` - Assembly language input.
- `opcode.txt` - Opcode information.
- `Output.png` - Screenshot of program output.
- `README.md` - Project documentation.

## Compile and Run
```bash
gcc symbol_table.c -o symbol_table
./symbol_table


