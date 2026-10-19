
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <limits.h>

FILE *out;

void processDirectory(const char *path);
void processFile(const char *filepath);

void processFile(const char *filepath)
{
    FILE *fp;
    char line[1024];
    char filename[256] = "";
    char description[768] = "";

    fp = fopen(filepath, "r");

    if (fp == NULL)
        return;

    while (fgets(line, sizeof(line), fp))
    {
        char *p = line;

        while (*p == ' ' || *p == '\t')
            p++;

        if (*p == '*' && strstr(p, ".c") != NULL)
        {
            char *end = strstr(p, ".c");
            size_t len = (size_t)(end - p + 2);

            if (len >= sizeof(filename))
                continue;

            memcpy(filename, p, len);
            filename[len] = '\0';

            memmove(filename, filename + 1, strlen(filename));

            p = end + 2;

            while (*p == ' ' || *p == '\t')
                p++;

            p[strcspn(p, "\r\n")] = '\0';

            snprintf(description, sizeof(description), "%s", p);

            printf("%-20s : %s\n", filename, description);
            fprintf(out, "%-20s : %s\n", filename, description);

            break;
        }
    }

    fclose(fp);
}

void processDirectory(const char *path)
{
    DIR *dir;
    struct dirent *entry;
    struct stat info;
    char fullpath[PATH_MAX];

    dir = opendir(path);

    if (dir == NULL)
    {
        perror(path);
        return;
    }

    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0)
            continue;

        int n = snprintf(fullpath, sizeof(fullpath),
                         "%s/%s", path, entry->d_name);

        if (n < 0 || (size_t)n >= sizeof(fullpath))
            continue;

        if (stat(fullpath, &info) != 0)
            continue;

        if (S_ISDIR(info.st_mode))
        {
            processDirectory(fullpath);
        }
        else
        {
            char *ext = strrchr(entry->d_name, '.');

            if (ext != NULL && strcmp(ext, ".c") == 0)
                processFile(fullpath);
        }
    }

    closedir(dir);
}

int main(void)
{
    char path[PATH_MAX];

    printf("Enter directory path: ");

    if (fgets(path, sizeof(path), stdin) == NULL)
        return 1;

    path[strcspn(path, "\r\n")] = '\0';

    out = fopen("output.txt", "w");

    if (out == NULL)
    {
        perror("output.txt");
        return 1;
    }

    printf("\nProgram Name\t\tDescription\n");
    printf("--------------------------------------------------------------------\n");

    fprintf(out, "Program Name\t\tDescription\n");
    fprintf(out, "--------------------------------------------------------------------\n");

    processDirectory(path);

    fclose(out);

    printf("\nAnalysis completed successfully.\n");
    printf("Output stored in output.txt\n");

    return 0;
}

