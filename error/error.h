#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#include <stdlib.h>

// #define DEBUG

#ifdef DEBUG
    #define PRINT_ERROR        if (code_error != ERR_NO) {my_strerr(code_error, stderr);}
    #define ERR_RET(ret_value) if (code_error == NULL || *code_error != 0) {return ret_value;}
#else
    #define PRINT_ERROR
    #define ERR_RET(...)
#endif

#define my_assert(expr, cd_err) if (!(expr)) {  \
        fprintf(stderr, "\x1b[31m%s %s:%d: My assertion failed: \"" #expr "\"\x1b[0m\n", __FILE__, __func__, __LINE__); \
        *code_error |= cd_err;  \
    }

enum code_error {
    ERR_NO                   = 0,
    ERR_PTR                  = 1 << 0,
    ERR_NAN                  = 1 << 1,
    ERR_MEM                  = 1 << 2,
    ERR_FOPEN                = 1 << 3,
    ERR_FCLOSE               = 1 << 4,
    ERR_FREAD                = 1 << 5,
    ERR_SYSTEM               = 1 << 6,
    ERR_DIV_ZERO             = 1 << 7,
    ERR_SQRT_NEGAT           = 1 << 8,
    ERR_LOG_NEGAT            = 1 << 9,

    ERR_LIST                 = 1 << 10,
    ERR_LIST_SIZE            = 1 << 11,
    ERR_LIST_HEAD            = 1 << 12,
    ERR_LIST_TAIL            = 1 << 13,
    ERR_LIST_FREE            = 1 << 14,
    ERR_LIST_DATA            = 1 << 15,
    ERR_LIST_PTR_DATA        = 1 << 16,
    ERR_LIST_PTR_FREE        = 1 << 17,
    ERR_LIST_CNT_NODE        = 1 << 18,
    ERR_LIST_DATA_LOOP       = 1 << 19,
    ERR_LIST_FREE_LOOP       = 1 << 20,

    LIST_POINTER_GARBAGE     = 1 << 21,

    ERR_LIST_INSERT          = 1 << 22,
    ERR_LIST_DELETE          = 1 << 23,
    ERR_LIST_REALLOC         = 1 << 24,

    ERR_HASH_TABLE           = 1 << 25,
    ERR_HASH_TABLE_INIT      = 1 << 26,
    ERR_HASH_TABLE_SIZE      = 1 << 27,
    ERR_HASH_TABLE_DATA      = 1 << 28,
    ERR_HASH_TABLE_HASH_FUNC = 1 << 29,

    ERR_HASH_REALLOC         = 1 << 30,

    ERR_CNT                  = 31
};

void my_strerr (const int code_error, FILE *stream);

#endif // ERROR_H
