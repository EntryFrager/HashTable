#include <x86intrin.h>
#include <stdint.h>

#include "../include/hash_table.h"
#include "../include/test.h"

int main ()
{
    uint64_t ticks = __rdtsc();

    test_second_part();

    free_ptr_dyn_mem();

    ticks = __rdtsc() - ticks;

    printf("%ld\n", ticks);

    return 0;
}
