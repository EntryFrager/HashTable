#ifndef HASH_FUNC_H
#define HASH_FUNC_H

#include "./hash_table.h"
#include "../error/error.h"

hash_t nul_hash_func              (const hash_elem_t elem, int *code_error);
hash_t ascii_code_hash_func       (const hash_elem_t elem, int *code_error);
hash_t len_word_hash_func         (const hash_elem_t elem, int *code_error);
hash_t control_sum_hash_func      (const hash_elem_t elem, int *code_error);
hash_t average_value_hash_func    (const hash_elem_t elem, int *code_error);
hash_t ror_hash_func              (const hash_elem_t elem, int *code_error);
hash_t rol_hash_func              (const hash_elem_t elem, int *code_error);
hash_t crc32_hash_func            (const hash_elem_t elem, int *code_error);
hash_t sse_crc32_hash_func        (const hash_elem_t elem, int *code_error);
hash_t inline_asm_crc32_hash_func (const hash_elem_t elem, int *code_error);

#endif // HASH_FUNC_H
