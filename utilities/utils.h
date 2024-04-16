#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>

#include "../error/error.h"

#define compare(first_value, second_value) compare_number(first_value, second_value, code_error)

#define fopen_(fp, fp_name, mode)               \
    FILE *fp = fopen(fp_name, mode);            \
    my_assert(fp != NULL, ERR_FOPEN);

#define fclose_(fp)                             \
    my_assert(fclose(fp) == 0, ERR_FCLOSE);

#define calloc_(var_name, type, size, size_elem)            \
    type var_name = (type) calloc(size, size_elem);         \
    my_assert(var_name != NULL, ERR_MEM);

#define calloc_init_(var_name, type, size, size_elem)       \
    var_name = (type) calloc(size, size_elem);              \
    my_assert(var_name != NULL, ERR_MEM);

#define calloc_g_(var_name, type, size, size_elem)          \
    calloc_(var_name, type, size, size_elem);               \
    add_pointer_dyn_mem((void *) var_name, code_error);

#define calloc_init__g_(var_name, type, size, size_elem)    \
    calloc_init_(var_name, type, size, size_elem);          \
    add_pointer_dyn_mem((void *) var_name, code_error);

#define malloc_(var_name, type, size)                       \
    type var_name = (type) malloc(size);                    \
    my_assert(var_name != NULL, ERR_MEM);

#define malloc_init_(var_name, type, size)                  \
    var_name = (type) malloc(size);                         \
    my_assert(var_name != NULL, ERR_MEM);

#define malloc_g_(var_name, type, size, size_elem)          \
    malloc_(var_name, type, size, size_elem);               \
    add_pointer_dyn_mem((void *) var_name, code_error);

#define malloc_init_g_(var_name, type, size, size_elem)     \
    malloc_init_(var_name, type, size, size_elem);          \
    add_pointer_dyn_mem((void *) var_name, code_error);

#define realloc_(ptr, type, new_size)                       \
    ptr = (type) realloc(ptr, new_size);                    \
    my_assert(ptr != NULL, ERR_MEM);

const double EPSILON = 1e-10;

char *get_file_to_str (FILE *stream, size_t *size_file, int *code_error);

size_t get_file_size (FILE *stream, int *code_error);

char *get_str (FILE *stream, int *code_error);

size_t get_n_lines (char *str, int *code_error);

char *skip_isspace (char *str, size_t len_str, int *code_error);

char *read_ident (char **str, int *code_error);

int compare_number (const double value_1, const double value_2, int *code_error);

void clean_buffer ();

void create_folder (const char *folder_name, int *code_error);

void add_pointer_dyn_mem (void *ptr_dyn_mem, int *code_error);

void free_ptr_dyn_mem ();

#endif //UTILS_H
