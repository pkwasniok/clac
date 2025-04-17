#include "../stack.h"

void operator_handler_add(Stack* stack) {
    StackItem rhs, lhs, result;

    stack_pop_type(stack, NUMBER, &rhs);

    stack_pop_type(stack, NUMBER, &lhs);

    result.type = NUMBER;
    result.data.number = lhs.data.number + rhs.data.number;

    stack_push(stack, result);

    return;
}

