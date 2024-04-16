#ifndef HASH_TABLE_CPP
#define HASH_TABLE_CPP

#include "../include/hash_table.h"
#include "../include/hash_table_statistics.h"

static const int LIST_SIZE = 2;

#ifdef MAKE_PLOT
    static const char *FILE_NAME_CSV    = "table.csv";
    static const char *FOLDER_PLOT_FILE = "./plot";
    static const char *CMD_PLOT_PY      = "python3 ./make_graphics.py";
#endif

#ifdef HASH_TABLE_DEBUG
    static const char *HASH_TABLE_FOLDER_ERR  = "./debug";
    static const char *HASH_TABLE_FP_ERR_NAME = "./debug/hash_table/file_err.txt";
#endif

static inline void check_list_for_availability (HashTable *hash_table, const hash_t hash, int *code_error);

void *hash_init (HashTable *hash_table, hash_func_t hash_func, const int hash_table_size, int *code_error)
{
    hash_table->size = hash_table_size;

    calloc_init_(hash_table->data, List **, hash_table->size, sizeof(List *));

    hash_table->hash_func = hash_func;

    hash_table->n_load_elements = 0;

    hash_table->is_init = true;

    assert_hash_table(hash_table);

    return hash_table;
}

void hash_filling (HashTable *hash_table, const hash_elem_t *data, const size_t n_elems, int *code_error)
{
    assert_hash_table(hash_table);
    my_assert(data != NULL, ERR_PTR);

    for (size_t i = 0; i < n_elems; i++)
    {
        hash_insert_elem(hash_table, data[i], code_error);
    }

    assert_hash_table(hash_table);
}

void hash_insert_elem (HashTable *hash_table, const hash_elem_t elem, int *code_error)
{
    assert_hash_table(hash_table);

    hash_t hash_elem = hash_table->hash_func(elem, code_error) % hash_table->size;

    check_list_for_availability(hash_table, hash_elem, code_error);

    list_insert_elem(hash_table->data[hash_elem], elem, code_error);

    hash_table->n_load_elements++;

    assert_hash_table(hash_table);
}

void check_list_for_availability (HashTable *hash_table, const hash_t hash, int *code_error)
{
    if (hash_table->data[hash] == NULL)
    {
        hash_table->data[hash] = list_init(LIST_SIZE, code_error);
    }
}

int *hash_find_elem (const HashTable *hash_table, const hash_elem_t elem, int *code_error)
{
    assert_hash_table(hash_table);

    hash_t hash_elem = hash_table->hash_func(elem, code_error);

    static int pos_elem[2] = {};

    pos_elem[0] = (int) hash_elem;

    for (int i = 0; i < hash_table->data[hash_elem]->size; i++)
    {
        if (strcmp(elem, hash_table->data[hash_elem]->data[i].value) == 0)
        {
            pos_elem[1] = i;

            return pos_elem;
        }
    }

    return NULL;
}

void hash_delete_elem (HashTable *hash_table, const hash_elem_t elem, int *code_error)
{
    assert_hash_table(hash_table);
    my_assert(elem != NULL, ERR_PTR);

    int *pos_elem = hash_find_elem(hash_table, elem, code_error);

    if (hash_table->data[pos_elem[0]]->size == LIST_SIZE)
    {
        list_deinit(hash_table->data[pos_elem[0]], code_error);
    }
    else
    {
        list_delete_elem(hash_table->data[pos_elem[0]], (int) pos_elem[1], code_error);
    }

    assert_hash_table(hash_table);
}

#ifdef MAKE_PLOT

void make_plot (const HashTable *hash_table, const char *name_hash_func, int *code_error)
{
    assert_hash_table(hash_table);

    create_folder(FOLDER_PLOT_FILE, code_error);

    char file_name[50] = "";

    sprintf(file_name, "%s/%s_%s", FOLDER_PLOT_FILE, name_hash_func, FILE_NAME_CSV);

    fopen_(fp_hash_plot, file_name, "w+");

    for (int i = 1; i <= hash_table->size; i++)
    {
        if (hash_table->data[i - 1] == NULL)
        {
            fprintf(fp_hash_plot, "%d; 0\n", i);
            continue;
        }

        fprintf(fp_hash_plot, "%d; %d\n", i, hash_table->data[i - 1]->size);
    }

    fclose_(fp_hash_plot);

    char make_plot_cmd[100] = "";
    sprintf(make_plot_cmd, "%s %s %s", CMD_PLOT_PY, file_name, name_hash_func);

    my_assert(system(make_plot_cmd) != -1, ERR_SYSTEM);
}

#endif

void hash_destroy (HashTable *hash_table, int *code_error)
{
    assert_hash_table(hash_table);

    for (int i = 0; i < hash_table->size; i++)
    {
        if (hash_table->data[i] != NULL)
        {
            list_deinit(hash_table->data[i], code_error);
        }
    }

    free(hash_table->data);

    hash_table->data      = NULL;
    hash_table->hash_func = NULL;

    hash_table->size            = 0;
    hash_table->n_load_elements = 0;

    hash_table->is_init = false;
}

#ifdef HASH_TABLE_DEBUG

void hash_table_verificator (const HashTable *hash_table, int *code_error)
{
    my_assert(hash_table != NULL, ERR_HASH_TABLE);

    my_assert(hash_table->is_init == true, ERR_HASH_TABLE_INIT);

    if (*code_error == ERR_NO)
    {
        my_assert(hash_table->size > 0, ERR_HASH_TABLE_SIZE);

        my_assert(hash_table->data != NULL, ERR_HASH_TABLE_DATA);

        my_assert(hash_table->hash_func != NULL, ERR_HASH_TABLE_HASH_FUNC);

        if (*code_error == ERR_NO)
        {
            for (int i = 0; i < hash_table->size; i++)
            {
                if (hash_table->data[i] != NULL)
                {
                    assert_list(hash_table->data[i]);
                }
            }
        }
    }
}

#define DUMP_LOG(str) fprintf(fp_err, str);
#define DUMP_LOG_PARAM(str, ...) fprintf(fp_err, str, __VA_ARGS__);

void hash_table_dump_text (const HashTable *hash_table, int *code_error, const char *file_err, const char *func_err, const int line_err)
{
    create_folder(HASH_TABLE_FOLDER_ERR, code_error);

    FOPEN_(fp_err, HASH_TABLE_FP_ERR_NAME, "a");

    my_strerr(*code_error, fp_err);

    DUMP_LOG_PARAM("hash table[%p] \"hash table\" called from %s(%d) %s\n", hash_table, file_err, line_err, func_err);

    if (fp_err == NULL)
    {
        my_strerr(*code_error, stderr);
    }
    else if (hash_table != NULL)
    {
        DUMP_LOG("{\n");

        DUMP_LOG_PARAM("\thash function[%p]\n", hash_table->hash_func);
        DUMP_LOG_PARAM("\tdata[%p]\n", hash_table->data);

        if (hash_table->data != NULL)
        {
            DUMP_LOG("\t{\n");

            if (hash_table->size > 0)
            {
                for (int i = 0; i < hash_table->size; i++)
                {
                    if (hash_table->data[i] != NULL)
                    {
                        DUMP_LOG_PARAM("\t\tdata[%d] = list[%p]\n", i, hash_table->data[i]);
                    }
                }
            }

            DUMP_LOG("\t}\n");
        }

        DUMP_LOG("}\n\n-----------------------------------------------------------\n");
    }

    FCLOSE_(fp_err);
}

#undef DUMP_LOG
#undef DUMP_LOG_PARAM

#endif

#endif // HASH_TABLE_CPP
