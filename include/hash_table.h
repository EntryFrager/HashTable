#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <math.h>

typedef unsigned long hash_t;

typedef char * hash_elem_t;

typedef hash_t (*hash_func_t)(const hash_elem_t elem, int *code_error);

#include "../list/list.h"
#include "./hash_func.h"

// #define HASH_TABLE_DEBUG
#define MAKE_PLOT

#ifdef HASH_TABLE_DEBUG
    #define assert_hash_table(hash_table)               \
    {                                                   \
        hash_table_verificator(hash_table, code_error); \
        if (*code_error != ERR_NO)                      \
        {                                               \
            hash_table_dump(hash_table, code_error);    \
        }                                               \
    }

    #define hash_table_dump(hash_table, code_error)                                     \
    {                                                                                   \
        hash_table_dump_text(hash_table, code_error, __FILE__, __func__, __LINE__);     \
    }
#else
    #define assert_hash_table(...)
    #define hash_table_dump(...)
#endif

typedef struct {
    bool is_init = false;
    int size = 0;
    int n_load_elements = 0;

    List **data = {};

    hash_func_t hash_func;
} HashTable;

void *hash_init (HashTable *hash_table, hash_func_t hash_func, const int hash_table_size, int *code_error);

void hash_filling (HashTable *hash_table, const hash_elem_t *data, const size_t n_elems, int *code_error);

void hash_insert_elem (HashTable *hash_table, const hash_elem_t elem, int *code_error);

int *hash_find_elem (const HashTable *hash_table, const hash_elem_t elem, int *code_error);

void hash_delete_elem (HashTable *hash_table, const hash_elem_t elem, int *code_error);

void make_plot (const HashTable *hash_table, const char *name_hash_func, int *code_error);

void hash_destroy (HashTable *hash_table, int *code_error);

#ifdef HASH_TABLE_DEBUG
    void hash_table_verificator (const HashTable *hash_table, int *code_error);

    void hash_table_dump_text (const HashTable *hash_table, int *code_error,
                               const char *file_err, const char *func_err,
                               const int line_err);
#endif

#endif // HASH_TABLE_H
