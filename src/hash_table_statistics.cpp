#ifndef HASH_TABLE_STATISTICS_CPP
#define HASH_TABLE_STATISTICS_CPP

#include "../include/hash_table_statistics.h"

static const char *FILE_NAME_CSV    = "table.csv";
static const char *FOLDER_PLOT_FILE = "./plot";
static const char *CMD_PLOT_PY      = "python3 ./make_graphics.py";

static void get_average_len_lists (HashTable *hash_table, StatisticsHashTable *stat, int *code_error);
static void get_dispersion (HashTable *hash_table, StatisticsHashTable *stat, int *code_error);

void get_statistic_hash_table (HashTable *hash_table, StatisticsHashTable *stat, const char *hash_func_name, int *code_error)
{
    assert_hash_table(hash_table);
    my_assert(stat != NULL, ERR_PTR);
    my_assert(hash_func_name != NULL, ERR_PTR);

    stat->hash_func_name = hash_func_name;

    stat->load_factor = (float) hash_table->n_load_elements / (float) hash_table->size;

    get_average_len_lists(hash_table, stat, code_error);

    get_dispersion(hash_table, stat, code_error);

    assert_hash_table(hash_table);
}

void get_average_len_lists (HashTable *hash_table, StatisticsHashTable *stat, int *code_error)
{
    assert_hash_table(hash_table);
    my_assert(stat != NULL, ERR_PTR);

    for (int i = 0; i < hash_table->size; i++)
    {
        if (hash_table->data[i] != NULL)
        {
            stat->average_len_lists += (float) hash_table->data[i]->tail;
        }
    }

    stat->average_len_lists /= (float) hash_table->size;

    my_assert(stat != NULL, ERR_PTR);
}

void get_dispersion (HashTable *hash_table, StatisticsHashTable *stat, int *code_error)
{
    assert_hash_table(hash_table);
    my_assert(stat != NULL, ERR_PTR);

    float deviation = 0;

    for (int i = 0; i < hash_table->size; i++)
    {
        if (hash_table->data[i] != NULL)
        {
            deviation = stat->average_len_lists - (float) hash_table->data[i]->tail;
            stat->disp += deviation * deviation;
        }
    }

    stat->disp /= (float) hash_table->size;

    my_assert(stat != NULL, ERR_PTR);
}

void print_statistic_hash_table (StatisticsHashTable *stat, FILE *stream, int *code_error)
{
    my_assert(stat != NULL, ERR_PTR);
    my_assert(stream != NULL, ERR_PTR);

    fprintf(stream, "The load factor for the %s hash function is %.1f\n", stat->hash_func_name, stat->load_factor);
    fprintf(stream,  "The dispersion for the %s hash function is %.0f\n\n", stat->hash_func_name, stat->disp);
}

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

#endif // HASH_TABLE_STATISTICS_CPP
