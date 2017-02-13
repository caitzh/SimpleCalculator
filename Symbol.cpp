//
// Created by caitzh on 17-2-13.
//

#include "Symbol.h"

Symbol::Symbol(TOKEN_TYPE token_type, double value, char id)
        : Token(token_type, value), id(id) {}

Symbol::Symbol(Token token) : Token(token), id(' ') {}

bool operator<(const Symbol a, const Symbol b) {
    if (a.type != b.type) return a.type < b.type;
    else if (a.value != b.value) return a.value < b.value;
    else return a.id < b.id;
}