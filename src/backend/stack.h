#pragma once

#define E_STACK_SUCCESS 0
#define E_STACK_NOMEM 1
#define E_STACK_FULL 2
#define E_STACK_EMPTY 3

typedef struct {
    enum { NUMBER } type;
    union { double number; } data;
} StackItem;

typedef struct {
    int pointer;
    int buffer_size;
    StackItem* buffer;
} Stack;

int stack_init(Stack*, int size);

void stack_deinit(Stack*);

int stack_push(Stack*, StackItem);

int stack_pop(Stack*, StackItem*);

int stack_getsize(Stack*);

