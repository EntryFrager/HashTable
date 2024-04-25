#ifndef PARS_CPP
#define PARS_CPP

#include "../include/pars.h"

static void print_hash_table_to_file (HashTable *hash_table, const char *file_name, int *code_error);

void pars_text_to_word(const char *file_name, int *code_error)
{
    my_assert(file_name != NULL, ERR_PTR);

    size_t len_data = 0;

    char **data = input_data(file_name, &len_data, code_error);
    ERR_RET();

    HashTable hash_table = {};
    hash_init(&hash_table, crc32_hash_func, (int) len_data, code_error);
    ERR_RET();

    hash_filling(&hash_table, data, len_data, code_error);
    ERR_RET();

    print_hash_table_to_file(&hash_table, file_name, code_error);
    ERR_RET();
}

void print_hash_table_to_file (HashTable *hash_table, const char *file_name, int *code_error)
{
    assert_hash_table(hash_table);
    my_assert(file_name != NULL, ERR_PTR);

    fopen_(fp_pars, file_name, "w");

    for (int i = 0; i < hash_table->size; i++)
    {
        if (hash_table->data[i] != NULL)
        {
            List *list = hash_table->data[i];
            int list_tail = list->tail;

            for (int j = 1; j <= list_tail; j++)
            {
                fprintf(fp_pars, "%s\n", list->data[j].value);
            }
        }
    }

    fclose_(fp_pars);
}

#endif
