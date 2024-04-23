#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Include_file/error/error.h"
#include "../Include_file/utilities/utils.h"

#ifdef DEBUG
    #define LIST_DEBUG
#endif

#ifdef LIST_DEBUG
    #define assert_list(list)                   \
    {                                           \
        list_verification(list, code_error);    \
        if (*code_error != ERR_NO)              \
        {                                       \
            list_dump(list, code_error);        \
        }                                       \
    }

    #define list_dump(list, code_error)                                         \
    {                                                                           \
        list_dump_text(list, code_error, __FILE__, __func__, __LINE__);         \
        list_dump_graph_viz(list, code_error, __FILE__, __func__, __LINE__);    \
    }
#else
    #define assert_list(...)
    #define list_dump(...)
#endif

typedef char * ELEMENT;

const int LIST_VALUE_VENOM = 0xABCDEF;

typedef struct {
    ELEMENT value;
    int next = LIST_VALUE_VENOM;
    int prev = LIST_VALUE_VENOM;
} Node;

typedef struct {
    Node *data = {};

    int size = LIST_VALUE_VENOM;

    int head = LIST_VALUE_VENOM;
    int tail = LIST_VALUE_VENOM;
    int free = LIST_VALUE_VENOM;

    bool is_init = false;
    bool is_linear = false;
} List;

List *list_init (const int size, int *code_error);

void list_insert_elem (List *list, const ELEMENT value, int *code_error);

void list_insert_elem_after_log (List *list, const ELEMENT value, const int ip, int *code_error);

void list_insert_elem_after_ph (List *list, const ELEMENT value, int ip, int *code_error);

void list_delete_elem (List *list, const int ip, int *code_error);

void lineariz_list (List *list, int *code_error);

void list_swap_elem (List *list, const int ip_1, const int ip_2, int *code_error);

void list_print (const List *list, int *code_error);

void list_deinit (List *list, int *code_error);

#ifdef LIST_DEBUG
    void list_verification (const List *list, int *code_error);

    void list_dump_text (const List *list, int *code_error,
                         const char *file_err, const char *func_err,
                         const int line_err);

    void list_dump_graph_viz (const List *list, int *code_error,
                              const char *file_err, const char *func_err,
                              const int line_err);
#endif

#endif //LIST_H
