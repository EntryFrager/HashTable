#ifndef UTILS_CPP
#define UTILS_CPP

#include "utils.h"

static const int COEF_REALLOC_UP = 2;

char *get_file_to_str (FILE *stream, size_t *size_file, int *code_error)
{
    my_assert(stream != NULL, ERR_PTR);
    my_assert(size_file != NULL, ERR_PTR);

    *size_file = get_file_size(stream, code_error);

    calloc_g_(buf, char *, *size_file + 1, sizeof(char));

    size_t read_size = fread(buf, sizeof (char), *size_file, stream);
    my_assert(read_size == *size_file, ERR_FREAD);

    buf[*size_file] = '\0';

    ERR_RET(NULL);

    return buf;
}

size_t get_file_size (FILE *stream, int *code_error)
{
    my_assert(stream != NULL, ERR_PTR);

    size_t start = ftell(stream);
    fseek(stream, start, SEEK_END);
    size_t size_file = ftell(stream);
    rewind(stream);

    return size_file;
}

char *get_str (FILE *stream, int *code_error)
{
    my_assert(stream != NULL, ERR_PTR);

    char ch = 0;

    size_t len = 0;
    size_t str_len = 10;

    calloc_g_(str, char *, str_len, sizeof(char));

    while (!isspace(ch = (char)fgetc(stream)))
    {
        str[len++] = ch;

        if (len == str_len)
        {
            realloc_(str, char *, str_len * COEF_REALLOC_UP);

            str_len *= COEF_REALLOC_UP;
        }
    }

    str[len++] = '\0';
    realloc_(str, char *, len);

    ERR_RET(NULL);

    return str;
}

size_t get_n_lines (char *str, int *code_error)
{
    my_assert(str != NULL, ERR_PTR);

    size_t n_lines = 0;

    for (size_t i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == '\n')
        {
            n_lines++;
        }
    }

    return n_lines;
}

char *skip_isspace (char *str, size_t len_str, int *code_error)
{
    my_assert(str != NULL, ERR_PTR);

    calloc_g_(new_str, char *, len_str, sizeof(char));

    size_t pos = 0;

    for (size_t i = 0; i < len_str; i++)
    {
        if (!isspace(str[i]))
        {
            new_str[pos++] = str[i];
        }
    }

    realloc_(new_str, char *, (pos + 1) * sizeof(char));

    new_str[pos] = '\0';

    free(str);

    ERR_RET(NULL);

    return new_str;
}

char *read_ident (char **str, int *code_error)
{
    my_assert(str != NULL, ERR_PTR);

    calloc_g_(new_str, char *, strlen(*str), sizeof(char));

    size_t pos = 0;

    while (isalpha(**str) || **str == '_')
    {
        new_str[pos++] = **str;
        (*str)++;
    }

    realloc_(new_str, char *, pos + 1);

    new_str[pos] = '\0';

    ERR_RET(NULL);

    return new_str;
}

int compare_number (const double value_1, const double value_2, int *code_error)
{
    my_assert(isfinite (value_1), ERR_NAN);
    my_assert(isfinite (value_2), ERR_NAN);

    if ((value_1 - value_2) > EPSILON)
    {
        return 1;
    }
    else if ((value_1 - value_2) < (-1) * EPSILON)
    {
        return -1;
    }

    return 0;
}

void clean_buffer ()
{
    int ch = 0;

    while (((ch = getchar()) != '\n') && (ch != EOF)) {}
}

void create_folder (const char *folder_name, int *code_error)
{
    my_assert(folder_name != NULL, ERR_PTR);

    struct stat st = {0};

    if (stat(folder_name, &st) == -1)
    {
        mkdir(folder_name, 0700);
    }
}

static size_t n_ptr_dyn_mem = 0;
static void **array_ptr_dyn_mem = NULL;

void add_pointer_dyn_mem(void *ptr_dyn_mem, int *code_error)
{
    my_assert(ptr_dyn_mem != NULL, ERR_PTR);

    if (array_ptr_dyn_mem == NULL)
    {
        calloc_init_(array_ptr_dyn_mem, void **, 5, sizeof(void *));
    }
    else if (n_ptr_dyn_mem == sizeof(array_ptr_dyn_mem))
    {
        realloc_(array_ptr_dyn_mem, void **, n_ptr_dyn_mem * COEF_REALLOC_UP)
    }

    array_ptr_dyn_mem[n_ptr_dyn_mem] = ptr_dyn_mem;
    n_ptr_dyn_mem++;
}

void free_ptr_dyn_mem ()
{
    for (size_t i = 0; i < n_ptr_dyn_mem; i++)
    {
        free(array_ptr_dyn_mem[i]);
        array_ptr_dyn_mem[i] = NULL;
    }

    free(array_ptr_dyn_mem);
    array_ptr_dyn_mem = NULL;

    n_ptr_dyn_mem = 0;
}

#endif // UTILS_CPP
