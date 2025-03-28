#pragma once

#include <stdio.h>

#define E_FULL -1
#define E_EMPTY   -2

typedef struct {
    enum { NUMBER } type;
    union { double number; } value;
} item_t;

int stack_init(int size);
int stack_push(item_t item);
int stack_pop(item_t *item);
void stack_unwind();
void stack_dump(char *path);
void stack_load(char *path);

