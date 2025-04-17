#include "interpreter.h"
#include "../../token.h"
#include "../stack.h"
#include <assert.h>
#include <stdio.h>

int operator_interprete(Stack* stack, Token token) {
    assert(token.type == OPERATOR);

    OperatorHandler handler = NULL;
    switch (token.value.operator) {
        case ADD:
            handler = &operator_handler_add;
            break;
        case SUBTRACT:
            handler = &operator_handler_subtract;
            break;
        case MULTIPLY:
            handler = &operator_handler_multiply;
            break;
        case DIVIDE:
            handler = &operator_handler_divide;
            break;
    }

    if (handler == NULL) {
        printf("Operator not found!\n");
        return 1;
    }

    if ((*handler)(stack)) {
        return 1;
    }

    return 0;
}

