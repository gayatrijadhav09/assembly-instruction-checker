
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_SYMBOLS 200
#define MAX_LINE 512

typedef struct {
    int id;
    char name[64];
    int size;
    char value[256];
    char section;
    int address;
    char status;
} Symbol;

Symbol symbols[MAX_SYMBOLS];
int symbol_count = 0;
int data_address = 0;
int text_address = 0;
char current_section = 'T';

char opcode_mnemonics[100][32];
int opcode_count = 0;

void uppercase(char *s) {
    for (int i = 0; s[i]; i++)
        s[i] = (char)toupper((unsigned char)s[i]);
}

void trim(char *s) {
    int start = 0;
    while (isspace((unsigned char)s[start]))
        start++;
    if (start)
        memmove(s, s + start, strlen(s + start) + 1);

    int end = (int)strlen(s) - 1;
    while (end >= 0 && isspace((unsigned char)s[end]))
        s[end--] = '\0';
}

int load_opcode_table(void) {
    FILE *fp = fopen("opcode.txt", "r");
    char line[MAX_LINE], word[32], mnemonic[32];

    if (!fp) {
        printf("Error: Cannot open opcode.txt\n");
        return 0;
    }

    while (fgets(line, sizeof(line), fp)) {
        char *p = line;
        int column = 0;

        while (sscanf(p, "%31s", word) == 1) {
            if (column == 1) {
                strcpy(mnemonic, word);
                uppercase(mnemonic);

                int found = 0;
                for (int i = 0; i < opcode_count; i++)
                    if (strcmp(opcode_mnemonics[i], mnemonic) == 0)
                        found = 1;

                if (!found && opcode_count < 100)
                    strcpy(opcode_mnemonics[opcode_count++], mnemonic);
                break;
            }

            while (*p && !isspace((unsigned char)*p))
                p++;
            while (*p && isspace((unsigned char)*p))
                p++;
            column++;
        }
    }

    fclose(fp);
    return opcode_count > 0;
}

int is_instruction(char *word) {
    char temp[32];
    snprintf(temp, sizeof(temp), "%s", word);
    uppercase(temp);

    for (int i = 0; i < opcode_count; i++)
        if (strcmp(temp, opcode_mnemonics[i]) == 0)
            return 1;

    return 0;
}

int find_symbol(char *name) {
    for (int i = 0; i < symbol_count; i++)
        if (strcmp(symbols[i].name, name) == 0)
            return i;
    return -1;
}

void add_symbol(char *name, int size, char *value,
                char section, int address, char status) {
    int index = find_symbol(name);

    if (index >= 0) {
        if (symbols[index].status == 'U' && status == 'D') {
            symbols[index].size = size;
            strcpy(symbols[index].value, value);
            symbols[index].section = section;
            symbols[index].address = address;
            symbols[index].status = 'D';
        } else if (status == 'D') {
            printf("Error: Duplicate symbol '%s'\n", name);
        }
        return;
    }

    if (symbol_count >= MAX_SYMBOLS)
        return;

    Symbol *s = &symbols[symbol_count];
    s->id = ++symbol_count;
    snprintf(s->name, sizeof(s->name), "%s", name);
    s->size = size;
    snprintf(s->value, sizeof(s->value), "%s", value);
    s->section = section;
    s->address = address;
    s->status = status;
}

int directive_size(char *word) {
    char temp[16];
    snprintf(temp, sizeof(temp), "%s", word);
    uppercase(temp);

    if (!strcmp(temp, "DB")) return 1;
    if (!strcmp(temp, "DW")) return 2;
    if (!strcmp(temp, "DD")) return 4;
    if (!strcmp(temp, "DQ")) return 8;
    return 0;
}

int data_size(char *value, int unit) {
    int total = 0, count = 1;
    char *p = value;
    char quote = 0;

    if (*p == '"' || *p == '\'') {
        quote = *p++;
        char *end = strchr(p, quote);
        if (end)
            total = (int)(end - p);
        else
            total = (int)strlen(p);
        p = end ? end + 1 : p + strlen(p);
        while (*p) {
            if (*p == ',') {
                count++;
                while (*p && *p != ',') p++;
            }
            if (*p) p++;
        }
        return total + (count - 1) * unit;
    }

    for (p = value; *p; p++)
        if (*p == ',') count++;

    return count * unit;
}

void process_line(char *line) {
    char original[MAX_LINE], upper[MAX_LINE];
    char name[64], directive[16], value[256];
    char *p, *colon;
    int consumed = 0;

    trim(line);
    if (!*line) return;

    strcpy(original, line);
    strcpy(upper, line);
    uppercase(upper);

    if (strstr(upper, "SECTION .DATA") == upper ||
        !strcmp(upper, ".DATA")) {
        current_section = 'D';
        return;
    }
    if (strstr(upper, "SECTION .TEXT") == upper ||
        !strcmp(upper, ".TEXT")) {
        current_section = 'T';
        return;
    }
    if (strstr(upper, "GLOBAL ") == upper ||
        strstr(upper, "EXTERN ") == upper)
        return;

    colon = strchr(line, ':');
    if (colon) {
        *colon = '\0';
        trim(line);
        add_symbol(line, 0, "-", current_section,
                   current_section == 'D' ? data_address : text_address, 'D');
        p = colon + 1;
        trim(p);
        if (!*p) return;
        memmove(original, p, strlen(p) + 1);
    }

    if (sscanf(original, "%63s %15s %n",
               name, directive, &consumed) >= 2) {
        int unit = directive_size(directive);
        if (unit) {
            p = original + consumed;
            trim(p);
            snprintf(value, sizeof(value), "%s", p);
            int size = data_size(value, unit);

            add_symbol(name, size, value, current_section,
                       current_section == 'D' ? data_address : text_address, 'D');
            if (current_section == 'D')
                data_address += size;
            return;
        }
    }

    char mnemonic[32], operands[256];
    if (sscanf(original, "%31s", mnemonic) == 1) {
        uppercase(mnemonic);
        if (is_instruction(mnemonic)) {
            p = original;
            while (*p && !isspace((unsigned char)*p)) p++;
            while (*p && isspace((unsigned char)*p)) p++;
            snprintf(operands, sizeof(operands), "%s", p);

            for (p = operands; *p;) {
                if (isalpha((unsigned char)*p) || *p == '_') {
                    char ref[64];
                    int i = 0;
                    while (isalnum((unsigned char)*p) || *p == '_') {
                        if (i < 63) ref[i++] = *p;
                        p++;
                    }
                    ref[i] = '\0';
                    char temp[64];
                    strcpy(temp, ref);
                    uppercase(temp);

                    if (strcmp(temp, "EAX") && strcmp(temp, "EBX") &&
                        strcmp(temp, "ECX") && strcmp(temp, "EDX") &&
                        !is_instruction(temp) && find_symbol(ref) < 0)
                        add_symbol(ref, 0, "-", '-', -1, 'U');
                } else {
                    p++;
                }
            }

            if (current_section == 'T')
                text_address += 4;
        }
    }
}

int main(void) {
    FILE *fp;
    char line[MAX_LINE];

    if (!load_opcode_table())
        return 1;

    fp = fopen("assembly.asm", "r");
    if (!fp) {
        printf("Error: Cannot open assembly.asm\n");
        return 1;
    }

    while (fgets(line, sizeof(line), fp)) {
        char *comment = strchr(line, ';');
        if (comment) *comment = '\0';
        process_line(line);
    }
    fclose(fp);

    printf("\nSYMBOL TABLE\n");
    printf("%-5s %-16s %-8s %-10s %-10s %-10s\n",
           "ID", "Name", "Size", "Section", "Address", "Status");

    for (int i = 0; i < symbol_count; i++) {
        printf("%-5d %-16s %-8d %-10c %-10s %-10c\n",
               symbols[i].id, symbols[i].name, symbols[i].size,
               symbols[i].section,
               symbols[i].address < 0 ? "-" : "set",
               symbols[i].status);
    }

    printf("\nData section size: %d bytes\n", data_address);
    printf("Text section size: %d bytes\n", text_address);

    for (int i = 0; i < symbol_count; i++)
        if (symbols[i].status == 'U')
            printf("Error: Undefined symbol '%s'\n", symbols[i].name);

    return 0;
}

