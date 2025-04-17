#pragma once
#include "../token.h"
#include "stack.h"

typedef void (*OperatorHandler)(void);

typedef struct {
    char symbol;
    OperatorHandler handler;
} Operator;

void operator_interprete(Stack* stack, token_t token);

