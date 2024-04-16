#ifndef HASH_TABLE_STATISTICS_H
#define HASH_TABLE_STATISTICS_H

#include "./hash_table.h"

typedef struct {
    float load_factor = 0;

    float average_len_lists = 0;

    float disp = 0;
} StatisticsHashTable;

void get_statistic_hash_table (HashTable *hash_table, StatisticsHashTable *stat, int *code_error);

#endif // HASH_TABLE_STATISTICS_H
