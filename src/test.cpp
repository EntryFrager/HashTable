#ifndef TEST_CPP
#define TEST_CPP

#include "../include/test.h"

extern "C" hash_t asm_crc32_hash_func (char *elem, int *code_error);

static const char *FILE_NAME = "./text/pars_text.txt";

static const int n_hash_func = 8;

static const char *hash_func_name[] = {"nul_hash_func",
                                       "ascii_code_hash_func",
                                       "len_word_hash_func",
                                       "control_sum_hash_func",
                                       "average_value_hash_func",
                                       "ror_hash_func",
                                       "rol_hash_func",
                                       "crc32_hash_func"};

static const hash_func_t hash_func[] = {nul_hash_func,
                                        ascii_code_hash_func,
                                        len_word_hash_func,
                                        control_sum_hash_func,
                                        average_value_hash_func,
                                        ror_hash_func,
                                        rol_hash_func,
                                        crc32_hash_func};

static const int hash_table_size = 2000;

void test_first_part ()
{
    int code_error = 0;

    size_t len_data = 0;

    char **data = input_data(FILE_NAME, &len_data, &code_error);

    for (int i = 0; i < n_hash_func; i++)
    {
        HashTable hash_table = {};
        hash_init(&hash_table, hash_func[i], hash_table_size, &code_error);

        hash_filling(&hash_table, data, len_data, &code_error);

        #ifdef GET_STATISTICS
            make_plot(&hash_table, hash_func_name[i], &code_error);
        #endif

        hash_destroy(&hash_table, &code_error);
    }
}

void test_second_part ()
{
    int code_error = 0;

    HashTable hash_table = {};
    hash_init(&hash_table, asm_crc32_hash_func, hash_table_size, &code_error);

    size_t len_data = 0;

    char **data = input_data(FILE_NAME, &len_data, &code_error);

    hash_filling(&hash_table, data, len_data, &code_error);

    for (size_t j = 0; j < 200; j++)
    {
        for (size_t i = 0; i < len_data; i++)
        {
            HashElemPos hash_elem_pos = {};
            hash_find_elem(&hash_table, &hash_elem_pos, data[i], &code_error);
        }
    }

    hash_destroy(&hash_table, &code_error);
}


#endif // TEST_CPP
