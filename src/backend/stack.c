#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

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
        return E_FULL;
    }

    stack_buffer[stack_ptr++] = item;

    return 0;
}

int stack_pop(item_t *item) {
    if (stack_ptr <= 0) {
        return E_EMPTY;
    }

    *item = stack_buffer[--stack_ptr];

    return 0;
}

int stack_len() {
    return stack_ptr;
}

void stack_unwind() {
    item_t item;

    while (!stack_pop(&item))
        ;

    free(stack_buffer);
}

void stack_dump(char *path) {
    FILE *file = fopen(path, "w");

    if (file == NULL) {
        return;
    }

    item_t item;
    while (!stack_pop(&item)) {
        fprintf(file, "%f ", item.value.number);
    }
    fprintf(file, "\n");

    fclose(file);
}

void stack_load(char *path) {
    FILE *file = fopen(path, "r");

    if (file == NULL) {
        return;
    }

    item_t item;
    item.type = NUMBER;
    while (fscanf(file, "%lf", &item.value.number) == 1) {
        stack_push(item);
    }

    fclose(file);
}

