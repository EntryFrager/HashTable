#ifndef HASH_TABLE_STATISTICS_CPP
#define HASH_TABLE_STATISTICS_CPP

#include "../include/hash_table_statistics.h"

static void get_average_len_lists (HashTable *hash_table, StatisticsHashTable *stat, int *code_error);
static void get_dispersion (HashTable *hash_table, StatisticsHashTable *stat, int *code_error);

void get_statistic_hash_table (HashTable *hash_table, StatisticsHashTable *stat, int *code_error)
{
    assert_hash_table(hash_table);
    my_assert(stat != NULL, ERR_PTR);

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

#endif // HASH_TABLE_STATISTICS_CPP
