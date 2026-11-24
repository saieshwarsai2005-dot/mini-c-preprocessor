#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cmdremoval.h"
#include "file_inclusion.h"
#include "macro_handler.h"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: ./mypreprocessor <inputfile.c>\n");
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        printf("File not found\n");
        return 1;
    }

    char out_file[256];
    strcpy(out_file, argv[1]);

    int i;
    for (i = 0; out_file[i] != '\0'; i++);
    if (i >= 2 && out_file[i - 2] == '.' && out_file[i - 1] == 'c')
    {
        out_file[i - 1] = 'i';
    }
    else
    {
        strcat(out_file, ".i");
    }

    FILE *fq = fopen(out_file, "w");
    if (fq == NULL)
    {
        printf("Error creating output file\n");
        fclose(fp);
        return 1;
    }

    FILE *tmp1 = tmpfile();
    FILE *tmp2 = tmpfile();
    if (tmp1 == NULL || tmp2 == NULL)
    {
        printf("Error creating temporary files\n");
        fclose(fp);
        fclose(fq);
        return 1;
    }

    remove_comments(fp, tmp1);
    rewind(tmp1);

    handle_includes(tmp1, tmp2);
    rewind(tmp2);

    handle_macros(tmp2, fq);

    fclose(tmp1);
    fclose(tmp2);
    fclose(fp);
    fclose(fq);
    return 0;
}
