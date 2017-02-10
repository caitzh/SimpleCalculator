//
// Created by caitzh on 17-2-10.
//

#include <iostream>
#include "LexicalAnalyser.h"

LexicalAnalyser::LexicalAnalyser(string input) {
    expression = input;
    index = 0;
}

string LexicalAnalyser::analyse(string input) {
    expression = input;
    index = 0;
    return analyse();
}

string LexicalAnalyser::analyse() {
    while (index < expression.size()) {
        if (!regonizeOperator() && !regonizeNumber() && !regonizeWhiteSpace()) {
            string error(expression);
            error += "\n";
            for (int i = 0; i < index; ++i) {
                error += " ";
            }
            error += "^\n";
            error += "Error: can not regonize '";
            error += expression[index];
            error += "'";
            return error;
        }
    }
    return "";
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
                return false;
        }
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
    if (state == 1 || state == 3) {
        double value = stringToNum(expression.substr(oldIndex, index-oldIndex));
        Token token(NUM, value);
        result.push_back(token);
        return true;
    } else {
        //index = oldIndex;
        return false;
    }
}

double LexicalAnalyser::stringToNum(string s) {
    int integer = 0, i;
    for (i = 0; i < s.size() && s[i] != '.'; ++i) {
        integer = integer * 10 + s[i] - '0';
    }
    double float_num = 0, pow = 0.1;
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
