
#include <stdio.h>
#include <string.h>

#define MAX_LINE 200

void processString(char *str)
{
    int i;

    printf("String : %s\n", str);

    printf("ASCII : ");
    for (i = 0; str[i] != '\0'; i++)
        printf("%d ", (unsigned char)str[i]);

    printf("\nHex : ");
    for (i = 0; str[i] != '\0'; i++)
        printf("%02X ", (unsigned char)str[i]);

    printf("\n\n");
}

void processNumber(unsigned int number)
{
    int i;

    printf("Decimal : %u\n", number);
    printf("Hexadecimal : %08X\n", number);

    printf("Little Endian Format : ");
    for (i = 0; i < 4; i++)
        printf("%02X ", (number >> (i * 8)) & 0xFF);

    printf("\n\n");
}

int main(void)
{
    FILE *file;
    char line[MAX_LINE];
    char *start, *end, *p;
    unsigned int number;

    file = fopen("input.asm", "r");

    if (file == NULL)
    {
        printf("Error: Cannot open input.asm\n");
        return 1;
    }

    printf("LITTLE ENDIAN CONVERSION\n\n");

    while (fgets(line, sizeof(line), file))
    {
        line[strcspn(line, "\r\n")] = '\0';

        p = strstr(line, "dd");

        if (p != NULL)
        {
            if (sscanf(p + 2, "%u", &number) == 1)
                processNumber(number);

            continue;
        }

        start = strchr(line, '"');
        if (start == NULL)
            start = strchr(line, '\'');

        if (start != NULL)
        {
            char quote = *start;
            end = strchr(start + 1, quote);

            if (end != NULL)
            {
                *end = '\0';
                processString(start + 1);
            }
        }
    }

    fclose(file);

    printf("Conversion completed successfully.\n");

    return 0;
}

