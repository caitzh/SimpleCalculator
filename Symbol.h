//
// Created by caitzh on 17-2-13.
//

#ifndef SIMPLECALCULATOR_SYMBOL_H
#define SIMPLECALCULATOR_SYMBOL_H


#include "Token.h"

// Symbol类，用于表示上下文无关文法的符号
// 如 E->E+T, E、+ 、T 都是 Symbol
struct Symbol : public Token {
    Symbol(TOKEN_TYPE token_type, double value = 0, char id = ' ');
    Symbol(Token token);

    char id; // 标志(identifier), 如 'E'
};

// 比较函数, 把 Symbol 用做 map 的 key 时需要用到
bool operator<(const Symbol a, const Symbol b);

#endif //SIMPLECALCULATOR_SYMBOL_H
