#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "macro_handler.h"

#define MAX_MACROS 100
#define MAX_PARAMS 10

typedef struct
{
    char name[64];
    int has_args;
    char params[MAX_PARAMS][64];
    int param_count;
    char body[512];
} Macro;

static Macro macros[MAX_MACROS];
static int macro_count = 0;

static int find_macro(const char *name)
{
    for (int i = 0; i < macro_count; i++)
    {
        if (strcmp(macros[i].name, name) == 0)
        {
            return i;
        }
    }
    return -1;
}

static void parse_define(const char *p)
{
    if (macro_count >= MAX_MACROS)
    {
        return;
    }

    p += 7; // Skip "#define"
    while (*p == ' ' || *p == '\t') p++;

    Macro *m = &macros[macro_count];
    m->has_args = 0;
    m->param_count = 0;

    int i = 0;
    while ((isalnum((unsigned char)*p) || *p == '_') && i < 63)
    {
        m->name[i++] = *p++;
    }
    m->name[i] = '\0';

    if (*p == '(')
    {
        m->has_args = 1;
        p++; // Skip '('
        while (*p && *p != ')' && m->param_count < MAX_PARAMS)
        {
            while (*p == ' ' || *p == '\t') p++;
            int j = 0;
            while ((isalnum((unsigned char)*p) || *p == '_') && j < 63)
            {
                m->params[m->param_count][j++] = *p++;
            }
            m->params[m->param_count][j] = '\0';
            if (j > 0)
            {
                m->param_count++;
            }
            while (*p == ' ' || *p == '\t' || *p == ',') p++;
        }
        if (*p == ')') p++;
    }

    while (*p == ' ' || *p == '\t') p++;

    int k = 0;
    while (*p && *p != '\n' && *p != '\r' && k < 511)
    {
        m->body[k++] = *p++;
    }
    m->body[k] = '\0';

    macro_count++;
}

static void expand_func_macro(const Macro *m, char args[MAX_PARAMS][128], int arg_count, FILE *out)
{
    const char *p = m->body;
    while (*p)
    {
        if (isalpha((unsigned char)*p) || *p == '_')
        {
            char word[64];
            int i = 0;
            while ((isalnum((unsigned char)*p) || *p == '_') && i < 63)
            {
                word[i++] = *p++;
            }
            word[i] = '\0';

            int replaced = 0;
            for (int j = 0; j < m->param_count && j < arg_count; j++)
            {
                if (strcmp(word, m->params[j]) == 0)
                {
                    fputs(args[j], out);
                    replaced = 1;
                    break;
                }
            }
            if (!replaced)
            {
                fputs(word, out);
            }
        }
        else
        {
            fputc(*p++, out);
        }
    }
}

void handle_macros(FILE *in, FILE *out)
{
    char line[1024];
    macro_count = 0;

    while (fgets(line, sizeof(line), in) != NULL)
    {
        char *p = line;
        while (*p == ' ' || *p == '\t') p++;

        if (strncmp(p, "#define", 7) == 0 && (p[7] == ' ' || p[7] == '\t'))
        {
            parse_define(p);
            continue;
        }

        p = line;
        int in_string = 0;

        while (*p)
        {
            if (*p == '"')
            {
                in_string = !in_string;
                fputc(*p++, out);
            }
            else if (!in_string && (isalpha((unsigned char)*p) || *p == '_'))
            {
                char word[64];
                int i = 0;
                while ((isalnum((unsigned char)*p) || *p == '_') && i < 63)
                {
                    word[i++] = *p++;
                }
                word[i] = '\0';

                int idx = find_macro(word);
                if (idx != -1)
                {
                    if (!macros[idx].has_args)
                    {
                        fputs(macros[idx].body, out);
                    }
                    else if (*p == '(')
                    {
                        p++; // Skip '('
                        char args[MAX_PARAMS][128];
                        int arg_count = 0;
                        int depth = 1;
                        int j = 0;

                        while (*p && depth > 0)
                        {
                            if (*p == '(') depth++;
                            else if (*p == ')') depth--;

                            if (depth == 0)
                            {
                                args[arg_count][j] = '\0';
                                if (j > 0 || arg_count > 0) arg_count++;
                                p++;
                                break;
                            }
                            else if (*p == ',' && depth == 1 && arg_count < MAX_PARAMS - 1)
                            {
                                args[arg_count][j] = '\0';
                                arg_count++;
                                j = 0;
                                p++;
                                while (*p == ' ' || *p == '\t') p++;
                            }
                            else
                            {
                                if (j < 127) args[arg_count][j++] = *p;
                                p++;
                            }
                        }
                        expand_func_macro(&macros[idx], args, arg_count, out);
                    }
                    else
                    {
                        fputs(word, out);
                    }
                }
                else
                {
                    fputs(word, out);
                }
            }
            else
            {
                fputc(*p++, out);
            }
        }
    }
}
