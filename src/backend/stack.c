#include "stack.h"
#include <stdlib.h>
#include <assert.h>

int stack_init(Stack* stack, int size) {
    assert(size > 0);

    StackItem* buffer = malloc(sizeof(StackItem) * size);

    if (buffer == NULL) {
        return E_STACK_NOMEM;
    }

    stack->buffer = buffer;
    stack->buffer_size = size;
    stack->pointer = 0;

    return E_STACK_SUCCESS;
}

void stack_deinit(Stack* stack) {
    assert(stack->buffer != NULL);

    free(stack->buffer);

    stack->buffer = NULL;
    stack->buffer_size = 0;
    stack->pointer = 0;
}

int stack_push(Stack* stack, StackItem item) {
    assert(stack->buffer != NULL);

    if (stack->pointer >= stack->buffer_size) {
        return E_STACK_FULL;
    }

    stack->buffer[stack->pointer++] = item;

    return E_STACK_SUCCESS;
}

int stack_pop(Stack* stack, StackItem* item) {
    assert(stack->buffer != NULL);

    if (stack->pointer == 0) {
        return E_STACK_EMPTY;
    }

    *item = stack->buffer[--stack->pointer];

    return E_STACK_SUCCESS;
}

int stack_getsize(Stack* stack) {
    assert(stack->buffer != NULL);

    return stack->pointer;
}

