#ifndef MY_STRCMP_H
#define MY_STRCMP_H

int inline_asm_my_strcmp (const char *str_1, const char *str_2);

int avx_my_strcmp (const char *str_1, const char *str_2);

#endif // MY_STRCMP_H
