#ifndef MY_STRCMP_H
#define MY_STRCMP_H

#include <immintrin.h>

extern "C" int asm_my_strcmp (const char *str_1, const char *str_2);

int inline_asm_my_strcmp (const char *str_1, const char *str_2);

inline int avx_my_strcmp (const char *str_1, const char *str_2);

inline int avx_my_strcmp (const char *str_1, const char *str_2)
{
    __m256i s1 = _mm256_loadu_si256((const __m256i*) str_1);
    __m256i s2 = _mm256_loadu_si256((const __m256i*) str_2);

    return ~(_mm256_movemask_epi8(_mm256_cmpeq_epi8(s1, s2)));
}

#endif // MY_STRCMP_H
