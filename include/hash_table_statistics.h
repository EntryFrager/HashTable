#ifndef HASH_TABLE_STATISTICS_H
#define HASH_TABLE_STATISTICS_H

#include "./hash_table.h"

typedef struct {
    const char *hash_func_name = NULL;

    float load_factor = 0;

    float average_len_lists = 0;

    float disp = 0;
} StatisticsHashTable;

void get_statistic_hash_table (HashTable *hash_table, StatisticsHashTable *stat, const char *hash_func_name,  int *code_error);

void print_statistic_hash_table (StatisticsHashTable *stat, FILE *stream, int *code_error);

void make_plot (const HashTable *hash_table, const char *name_hash_func, int *code_error);

#endif // HASH_TABLE_STATISTICS_H
