#pragma once
#include "../../token.h"
#include "../stack.h"

extern void operator_handler_add(Stack*);
extern void operator_handler_subtract(Stack*);
extern void operator_handler_multiply(Stack*);
extern void operator_handler_divide(Stack*);

typedef void (*OperatorHandler)(Stack*);

typedef struct {
    char symbol;
    OperatorHandler handler;
} Operator;

void operator_interprete(Stack* stack, token_t token);

