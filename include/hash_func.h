#ifndef HASH_FUNC_H
#define HASH_FUNC_H

#include <nmmintrin.h>

#include "./hash_table.h"
#include "../error/error.h"

inline hash_t nul_hash_func              (const hash_elem_t elem, int *code_error);
inline hash_t ascii_code_hash_func       (const hash_elem_t elem, int *code_error);
inline hash_t len_word_hash_func         (const hash_elem_t elem, int *code_error);
inline hash_t control_sum_hash_func      (const hash_elem_t elem, int *code_error);
inline hash_t average_value_hash_func    (const hash_elem_t elem, int *code_error);
inline hash_t ror_hash_func              (const hash_elem_t elem, int *code_error);
inline hash_t rol_hash_func              (const hash_elem_t elem, int *code_error);
inline hash_t crc32_hash_func            (const hash_elem_t elem, int *code_error);
inline hash_t sse_crc32_hash_func        (const hash_elem_t elem, int *code_error);
inline hash_t inline_asm_crc32_hash_func (const hash_elem_t elem, int *code_error);

extern "C" hash_t asm_crc32_hash_func (char *elem, int *code_error);

inline hash_t nul_hash_func (const hash_elem_t elem, int *code_error)
{
    my_assert(elem != NULL, ERR_PTR);

    return 0;
}

inline hash_t ascii_code_hash_func (const hash_elem_t elem, int *code_error)
{
    my_assert(elem != NULL, ERR_PTR);

    return (hash_t) *elem;
}

inline hash_t len_word_hash_func (const hash_elem_t elem, int *code_error)
{
    my_assert(elem != NULL, ERR_PTR);

    return (hash_t) strlen(elem);
}

inline hash_t control_sum_hash_func (const hash_elem_t elem, int *code_error)
{
    my_assert(elem != NULL, ERR_PTR);

    hash_t control_sum = 0;

    for (size_t i = 0; elem[i] != '\0'; i++)
    {
        control_sum += elem[i];
    }

    return control_sum;
}

inline hash_t average_value_hash_func (const hash_elem_t elem, int *code_error)
{
    my_assert(elem != NULL, ERR_PTR);

    return (hash_t) control_sum_hash_func(elem, code_error) / len_word_hash_func(elem, code_error);
}

inline hash_t ror_hash_func (const hash_elem_t elem, int *code_error)
{
    my_assert(elem != NULL, ERR_PTR);

    hash_t hash = 0;

    for (size_t i = 0; elem[i] != '\0'; i++)
    {
        hash = ((hash >> 1) | (hash << 31)) ^ elem[i];
    }

    return hash;
}

inline hash_t rol_hash_func (const hash_elem_t elem, int *code_error)
{
    my_assert(elem != NULL, ERR_PTR);

    hash_t hash = 0;

    for (size_t i = 0; elem[i] != '\0'; i++)
    {
        hash = ((hash << 1) | (hash >> 31)) ^ elem[i];
    }

    return hash;
}

const hash_t CRC_POLINOM = 0xEDB88320;

inline hash_t crc32_hash_func (const hash_elem_t elem, int *code_error)
{
    my_assert(elem != NULL, ERR_PTR);

    hash_t crc = 0xffffffff;

    for (size_t i = 0; elem[i] != '\0'; i++)
    {
        crc ^= elem[i];

        for (int bit = 0; bit < 8; bit++)
        {
            if (crc & 1)
            {
                crc = (crc >> 1) ^ CRC_POLINOM;
            }
            else
            {
                crc = crc >> 1;
            }
        }
    }

    return ~crc;
}

inline hash_t sse_crc32_hash_func (const hash_elem_t elem, int *code_error)
{
    my_assert(elem != NULL, ERR_PTR);

    hash_t hash = 0;

    for (size_t i = 0; elem[i] != '\0'; i++)
    {
        hash = _mm_crc32_u8(hash, elem[i]);
    }

    return hash;
}

inline hash_t inline_asm_crc32_hash_func (const hash_elem_t elem, int *code_error)
{
    my_assert(elem != NULL, ERR_PTR);

    hash_t hash = 0;

    __asm__("xor rax, rax                  \n\t"
            "mov eax, 0xffffffff           \n\t"
            "jmp .if_loop                  \n\t"
            ".loop:                        \n\t"
            "crc32 eax, byte ptr [%[elem]] \n\t"
            "inc %[elem]                   \n\t"
            ".if_loop:                     \n\t"
            "cmp byte ptr [%[elem]], 0     \n\t"
            "ja .loop                      \n\t"
            "mov %[hash], eax              \n\t"
            :[hash] "=m"(hash)
            :[elem] "d"(elem)
            :"%rax");

    return hash;
}

#endif // HASH_FUNC_H
