#include "operator.h"
#include <assert.h>
#include <stdio.h>
#include "../token.h"
#include "stack.h"
#include "operator/handlers.h"

#define LENGTHOF(array) (int) (sizeof(array) / sizeof(array[0]))

static Operator g_OPERATORS[] = {
    {'+', &operator_handler_add},
    {'-', &operator_handler_subtract},
    {'x', &operator_handler_multiply},
    {'/', &operator_handler_divide},
};

void operator_interprete(Stack* stack, token_t token) {
    assert(token.type == OPERATOR);

    for (int i = 0; i < LENGTHOF(g_OPERATORS); i++) {
        if (g_OPERATORS[i].symbol == token.value.operator) {
            (*g_OPERATORS[i].handler)();
            return;
        }
    }

    printf("Operator not found!\n");
}

