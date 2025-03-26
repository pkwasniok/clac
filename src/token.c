#include <stdio.h>
#include "token.h"

void print_token(token_t token) {
    switch (token.type) {

        case OPERATOR:
            printf("{operator, %c}\n", token.value.operator);
            break;

        case MACRO:
            printf("{macro, %s}\n", token.value.macro);
            break;

        case LITERAL_NUMBER:
            printf("{literal_number, %lf}\n", token.value.literal_number);
            break;

    }
}

