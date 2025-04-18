#include "interpreter.h"
#include <stdio.h>
#include <assert.h>

int literal_interprete(Stack* stack, Token token) {
    assert(token.type == LITERAL_NUMBER);

    StackItem item;
    item.type = NUMBER;
    item.data.number = token.value.literal_number;

    if (stack_push(stack, item)) {
        printf("Stack error!\n");
    }

    return 0;
}

