#pragma once
#include "../../token.h"
#include "../stack.h"

extern int operator_handler_add(Stack*);
extern int operator_handler_subtract(Stack*);
extern int operator_handler_multiply(Stack*);
extern int operator_handler_divide(Stack*);

typedef int (*OperatorHandler)(Stack*);

typedef struct {
    char symbol;
    OperatorHandler handler;
} Operator;

int operator_interprete(Stack* stack, token_t token);

