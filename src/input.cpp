#ifndef INPUT_CPP
#define INPUT_CPP

#include "../include/input.h"

static char **pars_text (char *text, size_t *len_data, int *code_error);

char **input_data (const char *file_name, size_t *len_data, int *code_error)
{
    my_assert(file_name != NULL, ERR_PTR);

    fopen_(fp_data, file_name, "r");

    size_t size_file = 0;

    char *text = get_file_to_str(fp_data, &size_file, code_error);
    ERR_RET(NULL);

    fclose_(fp_data);

    char **data = pars_text(text, len_data, code_error);
    ERR_RET(NULL);

    return data;
}

char **pars_text (char *text, size_t *len_data, int *code_error)
{
    my_assert(text != NULL, ERR_PTR);

    *len_data = get_n_lines(text, code_error);
    ERR_RET(NULL);

    calloc_g_(data, char **, *len_data, sizeof(hash_elem_t));

    char *word = NULL;

    for (size_t i = 0; i < *len_data; i++)
    {
        calloc_g_(str, char *, 32, sizeof(char));
        word = text;

        while (*text != '\n')
        {
            text++;
        }

        *(text++) = '\0';

        data[i] = strcpy(str, word);
    }

    return data;
}

#endif // INPUT_CPP
