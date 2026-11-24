#include <stdio.h>
#include <string.h>
#include "file_inclusion.h"

void handle_includes(FILE *in, FILE *out)
{
    char line[1024];

    while (fgets(line, sizeof(line), in) != NULL)
    {
        char *p = line;
        while (*p == ' ' || *p == '\t')
        {
            p++;
        }

        if (strncmp(p, "#include", 8) == 0)
        {
            char *start = strchr(p, '<');
            char *end = NULL;
            if (start != NULL)
            {
                end = strchr(start + 1, '>');
            }
            else
            {
                start = strchr(p, '"');
                if (start != NULL)
                {
                    end = strchr(start + 1, '"');
                }
            }

            if (start != NULL && end != NULL)
            {
                char inc_file[256];
                size_t len = (size_t)(end - start - 1);
                if (len < sizeof(inc_file))
                {
                    strncpy(inc_file, start + 1, len);
                    inc_file[len] = '\0';

                    FILE *inc_fp = fopen(inc_file, "r");
                    if (inc_fp == NULL)
                    {
                        char sys_path[512];
                        snprintf(sys_path, sizeof(sys_path), "/usr/include/%s", inc_file);
                        inc_fp = fopen(sys_path, "r");
                    }

                    if (inc_fp != NULL)
                    {
                        int ch;
                        while ((ch = fgetc(inc_fp)) != EOF)
                        {
                            fputc(ch, out);
                        }
                        fputc('\n', out);
                        fclose(inc_fp);
                        continue;
                    }
                }
            }
        }
        fputs(line, out);
    }
}
