SOURCE CODE FILE ANALYSIS

Name      : Gayatri Jadhav
Roll No   : 25111023
Course    : M.Sc. Computer Science

Assignment Description:

This program accepts a directory path from the user. It recursively scans the specified directory and all its subdirectories. The program searches for C source files (.c), extracts the program name and description from the initial comment block, displays the information on the screen, and saves the output in output.txt.

Files Submitted:

1. program.c - Source code
2. README.txt - Documentation
3. output.txt - Generated output

Compilation:

gcc program.c -o program

Execution:

./program

Input:

Enter the directory path containing the source code files.

Functions Used:

1. opendir() - Opens a directory.
2. readdir() - Reads directory entries.
3. closedir() - Closes a directory.
4. stat() - Checks file and directory information.
5. fopen() - Opens a file.
6. fgets() - Reads a line from a file.
7. fprintf() - Writes output to a file.
8. fclose() - Closes a file.
9. strstr() - Searches for a substring.
10. strrchr() - Finds the file extension.
11. strcmp() - Compares strings.
12. sprintf() - Creates the complete file path.

Problems Faced:

1. Understanding recursive directory traversal.
2. Finding only .c files.
3. Extracting program names and descriptions from comments.
4. Generating output.txt automatically.
5. Handling nested directories.

Conclusion:

This assignment demonstrates directory handling, file handling, string manipulation, and recursive directory traversal using C.
