#include "pars.h"

const char *file_name = "../onegin.txt";

int main ()
{
    int code_error = 0;

    pars_text_in_file(file_name, &code_error);

    PRINT_ERROR;

    return 0;
}