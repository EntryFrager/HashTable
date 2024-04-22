#ifndef PARS_CPP
#define PARS_CPP

#include "pars.h"
#include "../utilities/utils.h"

static const char *file_pars_text_name = "../text/pars_text.txt";

static char *input_file             (const char *file_name,       size_t *size_file, int *code_error);
static char *pars_buf               (      char *buf      , const size_t size_file , int *code_error);
static void print_pars_text_to_file (const char *buf                               , int *code_error);

void pars_text_in_file (const char *file_name, int *code_error)
{
    my_assert(file_name != NULL, ERR_PTR);

    size_t size_file = 0;

    char *buf = input_file(file_name, &size_file, code_error);
    ERR_RET();

    buf = pars_buf(buf, size_file, code_error);
    ERR_RET();

    print_pars_text_to_file(buf, code_error);
    ERR_RET();
}

char *input_file (const char *file_name, size_t *size_file, int *code_error)
{
    my_assert(size_file != NULL, ERR_PTR);

    FOPEN_(fp_text, file_name, "r");

    char *buf = get_file_to_str(fp_text, size_file, code_error);
    ERR_RET(NULL);

    FCLOSE_(fp_text);

    return buf;
}

char *pars_buf (char *buf, const size_t size_file, int *code_error)
{
    my_assert(buf != NULL, ERR_PTR);

    char *pars_buf = (char *) calloc(size_file, sizeof(char));

    size_t size_pars_buf = 0;

    for (size_t i = 0; i < size_file; i++)
    {
        if ((buf[i] >= 'A' && buf[i] <= 'Z') || (buf[i] >= 'a' && buf[i] <= 'z') || buf[i] == '\'')
        {
            pars_buf[size_pars_buf++] = buf[i];
        }
        else if (isspace(buf[i]))
        {
            pars_buf[size_pars_buf++] = '\n';

            while (!isalpha(buf[i]))
            {
                i++;
            }

            i--;
        }
    }

    pars_buf = (char *) realloc(pars_buf,size_pars_buf);

    free(buf);

    return pars_buf;
}

void print_pars_text_to_file(const char *buf, int *code_error)
{
    my_assert(buf != NULL, ERR_PTR);

    FOPEN_(fp_pars_text, file_pars_text_name, "w");

    fprintf(fp_pars_text, "%s", buf);

    FCLOSE_(fp_pars_text);
}

#endif
