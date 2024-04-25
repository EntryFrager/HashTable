#ifndef MY_STRCMP_CPP
#define MY_STRCMP_CPP

#include "../include/my_strcmp.h"

int avx_my_strcmp (const char *str_1, const char *str_2)
{
    __m256i s1 = _mm256_loadu_si256((const __m256i*) str_1);
    __m256i s2 = _mm256_loadu_si256((const __m256i*) str_2);

    return ~(_mm256_movemask_epi8(_mm256_cmpeq_epi8(s1, s2)));
}

int inline_asm_my_strcmp (const char *str_1, const char *str_2)
{
    int result = 0;

    __asm__("vmovdqu ymm1, ymmword ptr [rdi]\n\t"
            "vpcmpeqb ymm0, ymm1, ymmword ptr [rsi]\n\t"
            "vpmovmskb %[result], ymm0\n\t"
            "xor %[result], 0xffffffff\n\t"
            :[result]"=&r"(result)
            ::"%ymm0", "%ymm1", "%rax");

    return result;
}

#endif // MY_STRCMP_CPP
