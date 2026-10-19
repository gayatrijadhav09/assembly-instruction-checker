
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "opcode_reader.h"

#define MAX_LINE 300
#define MAX_WORD 30

static void toUpper(char str[])
{
    int i;

    for (i = 0; str[i] != '\0'; i++)
        str[i] = toupper((unsigned char)str[i]);
}

int mnemonicExists(char mnemonic[])
{
    FILE *fp;
    char line[MAX_LINE];
    char word[MAX_WORD];
    char *token;

    fp = fopen("opcode.txt", "r");

    if (fp == NULL)
    {
        printf("Cannot open opcode.txt\n");
        return 0;
    }

    toUpper(mnemonic);

    while (fgets(line, sizeof(line), fp))
    {
        token = strtok(line, " \t\r\n");

        while (token != NULL)
        {
            strcpy(word, token);
            toUpper(word);

            if (strcmp(word, mnemonic) == 0)
            {
                fclose(fp);
                return 1;
            }

            token = strtok(NULL, " \t\r\n");
        }
    }

    fclose(fp);
    return 0;
}

