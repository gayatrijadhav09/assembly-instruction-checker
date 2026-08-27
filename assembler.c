#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 26
#define MAX_NAME 20

char hashTable[SIZE][MAX_NAME];
int occupied[SIZE];

void toUpper(char str[])
{
    int i;

    for(i = 0; str[i] != '\0'; i++)
        str[i] = toupper((unsigned char)str[i]);
}

int hashFunction(char str[])
{
    return str[0] - 'A';
}

void insert(char mnemonic[])
{
    int index;
    int start;

    index = hashFunction(mnemonic);
    start = index;

    while(occupied[index] == 1)
    {
        if(strcmp(hashTable[index], mnemonic) == 0)
            return;

        index = (index + 1) % SIZE;

        if(index == start)
            return;
    }

    strcpy(hashTable[index], mnemonic);
    occupied[index] = 1;
}

int search(char mnemonic[])
{
    int index;
    int start;

    index = hashFunction(mnemonic);
    start = index;

    while(occupied[index] == 1)
    {
        if(strcmp(hashTable[index], mnemonic) == 0)
            return 1;

        index = (index + 1) % SIZE;

        if(index == start)
            return 0;
    }

    return 0;
}

void trim(char str[])
{
    int start = 0;
    int end;
    int i;

    while(isspace((unsigned char)str[start]))
        start++;

    end = strlen(str) - 1;

    while(end >= start &&
          isspace((unsigned char)str[end]))
    {
        str[end] = '\0';
        end--;
    }

    if(start > 0)
    {
        i = 0;

        while(str[start] != '\0')
        {
            str[i] = str[start];
            i++;
            start++;
        }

        str[i] = '\0';
    }
}

int isNumber(char str[])
{
    int i;

    if(str[0] == '\0')
        return 0;

    for(i = 0; str[i] != '\0'; i++)
    {
        if(!isdigit((unsigned char)str[i]))
            return 0;
    }

    return 1;
}

char *getOperandType(char operand[])
{
    int n;

    n = strlen(operand);

    if(n >= 2 &&
       operand[0] == '[' &&
       operand[n - 1] == ']')
    {
        return "Memory";
    }

    if(strcmp(operand, "EAX") == 0 ||
       strcmp(operand, "EBX") == 0 ||
       strcmp(operand, "ECX") == 0 ||
       strcmp(operand, "EDX") == 0 ||
       strcmp(operand, "ESP") == 0 ||
       strcmp(operand, "EBP") == 0 ||
       strcmp(operand, "ESI") == 0 ||
       strcmp(operand, "EDI") == 0)
    {
        return "Register";
    }

    if(isNumber(operand))
        return "Constant";

    return "Symbol";
}

int main()
{
    FILE *opcodeFile;
    FILE *assemblyFile;

    char line[300];
    char word[50];
    char previous[50];
    char mnemonic[20];

    char operandPart[150];
    char operand1[70];
    char operand2[70];

    char *token;
    char *comma;

    int i;
    int position;
    int lineNumber = 1;

    for(i = 0; i < SIZE; i++)
    {
        occupied[i] = 0;
        hashTable[i][0] = '\0';
    }

    opcodeFile = fopen("opcode.txt", "r");

    if(opcodeFile == NULL)
    {
        printf("Cannot open opcode.txt\n");
        return 1;
    }

    while(fgets(line, sizeof(line), opcodeFile))
    {
        token = strtok(line, " \t\n");
        previous[0] = '\0';

        while(token != NULL)
        {
            strcpy(word, token);

            if(strcmp(word, "1") == 0 ||
               strcmp(word, "2") == 0)
            {
                if(previous[0] != '\0')
                {
                    toUpper(previous);
                    insert(previous);
                }

                break;
            }

            strcpy(previous, word);
            token = strtok(NULL, " \t\n");
        }
    }

    fclose(opcodeFile);

    assemblyFile = fopen("program.asm", "r");

    if(assemblyFile == NULL)
    {
        printf("Cannot open program.asm\n");
        return 1;
    }

    while(fgets(line, sizeof(line), assemblyFile))
    {
        line[strcspn(line, "\r\n")] = '\0';

        trim(line);

        if(strlen(line) == 0)
            continue;

        if(sscanf(line, "%19s%n",
                  mnemonic, &position) != 1)
        {
            continue;
        }

        toUpper(mnemonic);

        strcpy(operandPart, line + position);
        trim(operandPart);

        printf("\nLine : %d\n", lineNumber);
        printf("Mnemonic : %s\n", mnemonic);

        if(search(mnemonic))
            printf("Exists : YES\n");
        else
            printf("Exists : NO\n");

        if(strlen(operandPart) == 0)
        {
            printf("Operand : None\n");
        }
        else
        {
            comma = strchr(operandPart, ',');

            if(comma != NULL)
            {
                *comma = '\0';

                strcpy(operand1, operandPart);
                strcpy(operand2, comma + 1);

                trim(operand1);
                trim(operand2);

                printf("Operand 1 : %s\n", operand1);
                printf("Type : %s\n",
                       getOperandType(operand1));

                printf("Operand 2 : %s\n", operand2);
                printf("Type : %s\n",
                       getOperandType(operand2));
            }
            else
            {
                strcpy(operand1, operandPart);
                trim(operand1);

                printf("Operand : %s\n", operand1);
                printf("Type : %s\n",
                       getOperandType(operand1));
            }
        }

        lineNumber++;
    }

    fclose(assemblyFile);

    return 0;
}
