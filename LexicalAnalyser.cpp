//
// Created by caitzh on 17-2-10.
//

#include <iostream>
#include "LexicalAnalyser.h"
#include "CalculatorException.h"

LexicalAnalyser::LexicalAnalyser(const string input) {
    expression = input;
    index = 0;
}

const vector<Token>& LexicalAnalyser::analyse(const string input) {
    expression = input;
    index = 0;
    result.clear(); // 清除上次计算结果
    return analyse();
}

const vector<Token>& LexicalAnalyser::analyse() {
    while (index < expression.size()) {
        if (!regonizeOperator() && !regonizeNumber() && !regonizeWhiteSpace()) {
            string error(expression);
            error += "\n";
            for (int i = 0; i < index; ++i) {
                error += " ";
            }
            error += "^\n";
            error += "LexicalError: can not regonize '";
            error += expression[index];
            error += "'";
            throw CalculatorException(error);
        }
    }
    result.push_back(Token(END)); //加入结束标志,即'$'
    return result;
}

bool LexicalAnalyser::regonizeOperator() {
    if (index < expression.size()) {
        TOKEN_TYPE type;
        switch (expression[index]) {
            case '+':
                type = ADD;
                break;
            case '-':
                type = SUB;
                break;
            case '*':
                type = MUL;
                break;
            case '/':
                type = DIV;
                break;
            case '(':
                type = LEFT_PAREN;
                break;
            case ')':
                type = RIGHT_PAREN;
                break;
            default:
                return false; // 识别运算符失败
        }
        // 识别成功，加入 result
        Token token(type);
        result.push_back(token);
        index++;
        return true;
    }
    return false;
}

bool LexicalAnalyser::regonizeWhiteSpace() {
    int state = 0;
    while (index < expression.size()) {
        char c = expression[index];
        if (isspace(c)) {
            if (state == 0) state++;
        } else {
            break;
        }
        index++;
    }
    return state != 0;
}


bool LexicalAnalyser::regonizeNumber() {
    int state = 0, oldIndex = index;
    while (index < expression.size()) {
        char c = expression[index];
        bool flag = true;
        switch (state) {
            case 0:
            case 2:
                if (isdigit(c)) state++;
                else flag = false;
                break;
            case 1:
                if (c == '.') state++;
                else if (!isdigit(c)) flag = false;
                break;
            case 3:
                if (!isdigit(c)) flag = false;
                break;
            default:
                flag = false;
                break;
        }
        if (!flag) break;
        index++;
    }
    // 识别成功
    if (state == 1 || state == 3) {
        double value = stringToNum(expression.substr(oldIndex, index-oldIndex));
        Token token(NUM, value);
        result.push_back(token);
        return true;
    } else {
        // 识别失败
        return false;
    }
}

double LexicalAnalyser::stringToNum(const string s) {
    int integer = 0, i;
    // 转换整数部分
    for (i = 0; i < s.size() && s[i] != '.'; ++i) {
        integer = integer * 10 + s[i] - '0';
    }
    double float_num = 0, pow = 0.1;
    // 转换小数部分
    if (s[i] == '.') {
        for (int j = i+1; j < s.size(); ++j) {
            float_num += (s[j] - '0') * pow;
            pow /= 10;
        }
    }
    return integer + float_num;
}

const vector<Token> &LexicalAnalyser::getResult() {
    return result;
}
