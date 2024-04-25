#include "../include/hash_table.h"
#include "../include/test.h"
#include "../include/pars.h"

const size_t N_HASH_FUNC = 9;

const int HASH_TABLE_SIZE = 4901;

const char *FILE_NAME = "./text/pars_text.txt";

int main ()
{
    int code_error = 0;

    #ifdef PARS_TEXT
        pars_text_to_word(FILE_NAME, &code_error);
    #endif

    #ifdef RESEARCH_HASH_FUNC
        ResearchHashFunc research_hash_func[N_HASH_FUNC] = {{"nul_hash_func", nul_hash_func, 10},
                                                            {"ascii_code_hash_func", ascii_code_hash_func, HASH_TABLE_SIZE},
                                                            {"len_word_hash_func", len_word_hash_func, HASH_TABLE_SIZE},
                                                            {"control_sum_hash_func_4901", control_sum_hash_func, HASH_TABLE_SIZE},
                                                            {"control_sum_hash_func_500", control_sum_hash_func, 500},
                                                            {"average_value_hash_func", average_value_hash_func, HASH_TABLE_SIZE},
                                                            {"ror_hash_func", ror_hash_func, HASH_TABLE_SIZE},
                                                            {"rol_hash_func", rol_hash_func, HASH_TABLE_SIZE},
                                                            {"crc32_hash_func", crc32_hash_func, HASH_TABLE_SIZE}};

        test_first_part(FILE_NAME, research_hash_func, N_HASH_FUNC, &code_error);
    #else
        test_second_part(FILE_NAME, HASH_TABLE_SIZE, &code_error);
    #endif

    return 0;
}
