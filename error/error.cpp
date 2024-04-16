#ifndef ERROR_CPP
#define ERROR_CPP

#include "error.h"

#define DEF_ERR(name) name,

static const char *err_msgs_arr[] = {
    #include "error_name.h"
};

#undef DEF_ERR

void my_strerr (const int code_error, FILE *stream)
{
    for (int i = 0; i < ERR_CNT; i++)
    {
        if (code_error & (1 << i))
        {
            printf("%d\n", i);
            fprintf(stream, "\x1b[31mERROR: %s\x1b[0m\n", err_msgs_arr[i]);
        }
    }
}

#endif // ERROR_CPP
