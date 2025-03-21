#include "args.h"
#include <string.h>

void parse_args(int argc, char **argv, char *expression) {
    for (int i = 1; i < argc; i++) {
        for (size_t j = 0; j < strlen(argv[i]); j++) {
            *(expression++) = argv[i][j];
        }
        *(expression++) = ' ';
    }
    *(--expression) = '\0';
}

