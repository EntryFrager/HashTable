#ifndef TEST_H
#define TEST_H

#include "./hash_table.h"
#include "../include/input.h"

// #define RESEARCH_HASH_FUNC

#ifdef RESEARCH_HASH_FUNC
    #include "../include/hash_table_statistics.h"
#endif

typedef struct {
    const char *hash_func_name = NULL;
    const hash_func_t hash_func = NULL;

    const int hash_table_size = 0;
} ResearchHashFunc;

void test_first_part (const char *file_name, ResearchHashFunc *hash_func, size_t n_hash_func, int *code_error);

void test_second_part (const char *file_name, const int hash_table_size, int *code_error);

#endif
