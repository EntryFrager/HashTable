#ifndef TEST_CPP
#define TEST_CPP

#include "../include/test.h"

void test_hash(HashTable *hash_table, char **data, size_t len_data, int *code_error)
{
    assert_hash_table(hash_table);
    my_assert(data != NULL, ERR_PTR);

    for (size_t j = 0; j < 200; j++)
    {
        for (size_t i = 0; i < len_data; i++)
        {
            HashElemPos hash_elem_pos = {};
            hash_find_elem(hash_table, &hash_elem_pos, data[i], code_error);
        }
    }
}


#endif // TEST_CPP
