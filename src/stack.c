#include "stack.h"
#include <stdlib.h>

item_t *stack_buffer = NULL;
int stack_size = 0;
int stack_ptr = 0;

int stack_init(int size) {
    stack_buffer = calloc(size, sizeof(item_t));
    stack_size = size;
    stack_ptr = 0;

    return 0;
}

int stack_push(item_t item) {
    if (stack_ptr >= stack_size) {
        return EFULL;
    }

    stack_buffer[stack_ptr++] = item;

    return 0;
}

int stack_pop(item_t *item) {
    if (stack_ptr <= 0) {
        return EEMPTY;
    }

    *item = stack_buffer[--stack_ptr];

    return 0;
}

