#include "../include/hash_table.h"
#include "../include/input.h"
#include "../include/hash_table_statistics.h"

const char *FILE_NAME = "./pars_text.txt";

int main ()
{
    int code_error = 0;

    static hash_func_t hash_func[] = {nul_hash_func,
                                      ascii_code_hash_func,
                                      len_word_hash_func,
                                      control_sum_hash_func,
                                      average_value_hash_func,
                                      ror_hash_func,
                                      rol_hash_func,
                                      crc32_hash_func};

    static const char *hash_func_name[] = {"nul_hash_func",
                                           "ascii_code_hash_func",
                                           "len_word_hash_func",
                                           "control_sum_hash_func",
                                           "average_value_hash_func",
                                           "ror_hash_func",
                                           "rol_hash_func",
                                           "crc32_hash_func"};

    const int hash_table_size = 2000;

    for (size_t i = 0; i < 8; i++)
    {
        HashTable hash_table = {};
        hash_init(&hash_table, hash_func[i], hash_table_size, &code_error);

        size_t len_data = 0;

        char **data = input_data(FILE_NAME, &len_data, &code_error);

        hash_filling(&hash_table, data, len_data, &code_error);

        StatisticsHashTable stat = {};
        get_statistic_hash_table(&hash_table, &stat, &code_error);

        printf("load factor for %ld hash_func: %lg\n", i + 1, stat.load_factor);
        printf( "dispersion for %ld hash_func: %lg\n", i + 1, stat.disp);

        hash_table_dump(&hash_table, &code_error);

        make_plot(&hash_table, hash_func_name[i], &code_error);

        hash_destroy(&hash_table, &code_error);

        free_ptr_dyn_mem();
    }

    return 0;
}
