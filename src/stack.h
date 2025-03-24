#pragma once

#define EFULL -1
#define EEMPTY   -2

typedef struct {
    enum { NUMBER } type;
    union { double number; } value;
} item_t;

int stack_init(int size);
int stack_push(item_t item);
int stack_pop(item_t *item);

