#include "../include/hash_table.h"
#include "../include/input.h"
#include "../include/test.h"

#ifdef GET_STATISTICS
    #include "../include/hash_table_statistics.h"
#endif

extern "C" hash_t asm_crc32_hash_func (char *elem, int *code_error);

const char *FILE_NAME = "./pars_text.txt";

const char *hash_func_name[] = {"nul_hash_func",
                                "ascii_code_hash_func",
                                "len_word_hash_func",
                                "control_sum_hash_func",
                                "average_value_hash_func",
                                "ror_hash_func",
                                "rol_hash_func",
                                "crc32_hash_func",
                                "sse_crc32_hash_func",
                                "asm_crc32_hash_func",
                                "inline_asm_crc32_hash_func"};

const hash_func_t hash_func[] = {nul_hash_func,
                                ascii_code_hash_func,
                                len_word_hash_func,
                                control_sum_hash_func,
                                average_value_hash_func,
                                ror_hash_func,
                                rol_hash_func,
                                crc32_hash_func,
                                sse_crc32_hash_func,
                                asm_crc32_hash_func,
                                inline_asm_crc32_hash_func};

const int hash_table_size = 2000;

int main ()
{
    int code_error = 0;

    HashTable hash_table = {};
    hash_init(&hash_table, hash_func[8], hash_table_size, &code_error);

    size_t len_data = 0;

    char **data = input_data(FILE_NAME, &len_data, &code_error);

    hash_filling(&hash_table, data, len_data, &code_error);

#ifdef GET_STATISTICS
    make_plot(&hash_table, hash_func_name[7], &code_error);
#endif

    test_hash(&hash_table, data, len_data, &code_error);

    hash_destroy(&hash_table, &code_error);

    free_ptr_dyn_mem();

    return 0;
}
