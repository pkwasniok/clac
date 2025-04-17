#pragma once

#define E_STACK_SUCCESS 0
#define E_STACK_NOMEM 1
#define E_STACK_FULL 2
#define E_STACK_EMPTY 3
#define E_STACK_TYPE 4

typedef enum {
    NUMBER
} StackItemType;

typedef union {
    double number;
} StackItemData;

typedef struct {
    StackItemType type;
    StackItemData data;
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

int stack_pop_type(Stack*, StackItemType, StackItem*);

int stack_getsize(Stack*);

