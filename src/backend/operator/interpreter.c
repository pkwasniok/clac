#include "interpreter.h"
#include <assert.h>
#include <stdio.h>
#include "../../token.h"
#include "../stack.h"

#define LENGTHOF(array) (int) (sizeof(array) / sizeof(array[0]))

static Operator g_OPERATORS[] = {
    {'+', &operator_handler_add},
    {'-', &operator_handler_subtract},
    {'x', &operator_handler_multiply},
    {'/', &operator_handler_divide},
};

int operator_interprete(Stack* stack, token_t token) {
    assert(token.type == OPERATOR);

    for (int i = 0; i < LENGTHOF(g_OPERATORS); i++) {
        if (g_OPERATORS[i].symbol == token.value.operator) {
            if ((*g_OPERATORS[i].handler)(stack))
                return 1;

            return 0;
        }
    }

    printf("Operator not found!\n");

    return 1;
}

