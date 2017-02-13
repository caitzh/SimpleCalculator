//
// Created by caitzh on 17-2-13.
//

#ifndef SIMPLECALCULATOR_SYMBOL_H
#define SIMPLECALCULATOR_SYMBOL_H


#include "Token.h"

struct Symbol : public Token {
    Symbol(TOKEN_TYPE token_type, double value = 0, char id = ' ');
    Symbol(Token token);

    char id;
};

bool operator<(const Symbol a, const Symbol b);

#endif //SIMPLECALCULATOR_SYMBOL_H
