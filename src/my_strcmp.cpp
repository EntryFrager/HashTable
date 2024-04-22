#ifndef MY_STRCMP_CPP
#define MY_STRCMP_CPP

#include "../include/my_strcmp.h"

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
