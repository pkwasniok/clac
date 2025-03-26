#pragma once
#include <stdlib.h>
#include "../token.h"

#define OPERATOR_ADD      '+'
#define OPERATOR_SUBTRACT '-'
#define OPERATOR_MULTIPLY '*'
#define OPERATOR_DIVIDE   '/'
#define OPERATOR_POWER    '^'

size_t tokenize(char *expression, token_t tokens[], size_t len);

