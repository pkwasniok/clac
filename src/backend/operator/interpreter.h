#pragma once
#include "../../token.h"
#include "../stack.h"

extern int operator_handler_add(Stack*);
extern int operator_handler_subtract(Stack*);
extern int operator_handler_multiply(Stack*);
extern int operator_handler_divide(Stack*);

typedef int (*OperatorHandler)(Stack*);

int operator_interprete(Stack* stack, Token token);

