#include "../stack.h"
#include <stdio.h>

int operator_handler_divide(Stack* stack) {
    StackItem rhs, lhs, result;

    stack_pop_type(stack, NUMBER, &rhs);

    stack_pop_type(stack, NUMBER, &lhs);

    if (rhs.data.number == 0) {
        printf("Operand error: cannot divide by zero!\n");
        return 1;
    }

    result.type = NUMBER;
    result.data.number = lhs.data.number / rhs.data.number;

    stack_push(stack, result);

    return 0;
}

