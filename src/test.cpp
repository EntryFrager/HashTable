#ifndef TEST_CPP
#define TEST_CPP

#include <x86intrin.h>
#include <stdint.h>

#include "../include/test.h"

#ifdef RESEARCH_HASH_FUNC

void test_first_part (const char *file_name, ResearchHashFunc *research_hash_func, size_t n_hash_func, int *code_error)
{
    my_assert(file_name != NULL, ERR_PTR);
    my_assert(research_hash_func != NULL, ERR_PTR);

    size_t len_data = 0;

    char **data = input_data(file_name, &len_data, code_error);
    ERR_RET();

    for (size_t i = 0; i < n_hash_func; i++)
    {
        HashTable hash_table = {};
        hash_init(&hash_table, research_hash_func[i].hash_func, research_hash_func[i].hash_table_size, code_error);
        ERR_RET();

        hash_filling(&hash_table, data, len_data, code_error);
        ERR_RET();

        make_plot(&hash_table, research_hash_func[i].hash_func_name, code_error);
        ERR_RET();

        StatisticsHashTable stat_hash_table = {};
        get_statistic_hash_table(&hash_table, &stat_hash_table, research_hash_func[i].hash_func_name, code_error);
        ERR_RET();

        print_statistic_hash_table(&stat_hash_table, stdout, code_error);

        hash_destroy(&hash_table, code_error);
        ERR_RET();
    }

    free_ptr_dyn_mem();
}

#else

void test_second_part (const char *file_name, const int hash_table_size, int *code_error)
{
    my_assert(file_name != NULL, ERR_PTR);

    HashTable hash_table = {};
    hash_init(&hash_table, asm_crc32_hash_func, hash_table_size, code_error);
    ERR_RET();

    size_t len_data = 0;

    char **data = input_data(file_name, &len_data, code_error);
    ERR_RET();

    hash_filling(&hash_table, data, len_data, code_error);
    ERR_RET();

    uint64_t ticks = __rdtsc();

    for (size_t j = 0; j < 10000; j++)
    {
        for (size_t i = 0; i < len_data; i++)
        {
            HashElemPos hash_elem_pos = {};
            hash_find_elem(&hash_table, &hash_elem_pos, data[i], code_error);
            ERR_RET();
        }
    }

    ticks = __rdtsc() - ticks;

    printf("Number of ticks spent on search: %ld\n", ticks);

    hash_destroy(&hash_table, code_error);
    ERR_RET();

    free_ptr_dyn_mem();
}

#endif

#endif // TEST_CPP
