//
// Created by caitzh on 17-2-10.
//

#ifndef SIMPLECALCULATOR_TOKEN_H
#define SIMPLECALCULATOR_TOKEN_H


//词法单元类型，加减乘除、左括号、右括号、数字
enum TOKEN_TYPE {ADD, SUB, MUL, DIV, LEFT_PAREN, RIGHT_PAREN, NUM};

class Token {
public:
    Token(TOKEN_TYPE token_type, double value_ = 0);

    TOKEN_TYPE type;
    double value;      //NUM(数字)类型才有value值
};


#endif //SIMPLECALCULATOR_TOKEN_H
