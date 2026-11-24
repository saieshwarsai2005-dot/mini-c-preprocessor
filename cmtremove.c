#include <stdio.h>
#include "cmdremoval.h"

void remove_comments(FILE *in, FILE *out)
{
    int ch, next;

    while ((ch = fgetc(in)) != EOF)
    {
        switch (ch)
        {
            case '/':
                next = fgetc(in);
                if (next == '/')
                {
                    while ((next = fgetc(in)) != '\n' && next != EOF);
                    if (next == '\n')
                    {
                        fputc('\n', out);
                    }
                }
                else if (next == '*')
                {
                    int prev = 0;
                    while ((next = fgetc(in)) != EOF)
                    {
                        if (prev == '*' && next == '/')
                        {
                            break;
                        }
                        prev = next;
                    }
                }
                else
                {
                    fputc(ch, out);
                    if (next != EOF)
                    {
                        ungetc(next, in);
                    }
                }
                break;

            case '"':
                fputc(ch, out);
                while ((ch = fgetc(in)) != EOF)
                {
                    fputc(ch, out);
                    if (ch == '\\')
                    {
                        next = fgetc(in);
                        if (next != EOF)
                        {
                            fputc(next, out);
                        }
                    }
                    else if (ch == '"')
                    {
                        break;
                    }
                }
                break;

            default:
                fputc(ch, out);
                break;
        }
    }
}
