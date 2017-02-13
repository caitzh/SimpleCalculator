//
// Created by caitzh on 17-2-11.
//

#include <iostream>
#include "SyntaxAnalyser.h"
#include "CalculatorException.h"

const string SyntaxAnalyser::grammarTable[9] = {
        "S->E",
        "E->E+T",
        "E->E-T",
        "E->T",
        "T->T*F",
        "T->T/F",
        "T->F",
        "F->(E)",
        "F->n"
};

// 前8列是 action 表, 后3列是 goto 表
const string SyntaxAnalyser::table[16][11] = {
        {"", "", "", "", "s9", "", "s14", "", "g1", "g2", "g13"},
        {"s3", "s4", "", "", "", "", "", "acc"},
        {"r3", "r3", "s5", "s6", "", "r3", "", "r3"},
        {"", "", "", "", "s9", "", "s14", "", "", "g10", "g13"},
        {"", "", "", "", "s9", "", "s14", "", "", "g11", "g13"},
        {"", "", "", "", "s9", "", "s14", "", "", "", "g7"},
        {"", "", "", "", "s9", "", "s14", "", "", "", "g8"},
        {"r4", "r4", "r4", "r4", "", "r4", "", "r4"},
        {"r5", "r5", "r5", "r5", "", "r5", "", "r5"},
        {"", "", "", "", "s9", "", "s14", "", "g12", "g2", "g13"},
        {"r1", "r1", "s5", "s6", "", "r1", "", "r1"},
        {"r2", "r2", "s5", "s6", "", "r2", "", "r2"},
        {"s3", "s4", "", "", "", "s15"},
        {"r6", "r6", "r6", "r6", "", "r6", "", "r6"},
        {"r8", "r8", "r8", "r8", "", "r8", "", "r8"},
        {"r7", "r7", "r7", "r7", "", "r7", "", "r7"}
};

void SyntaxAnalyser::initMapTable() {
    TOKEN_TYPE types[] = {ADD, SUB, MUL, DIV, LEFT_PAREN, RIGHT_PAREN, NUM, END};
    string no_terminal = "ETF";
    for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < 11; ++j) {
            string actionString = table[i][j];
            if (!actionString.empty()) {
                Action action = stringToAction(actionString);
                // 插入 Action 表
                if (j < 8)
                    actionTable[i].insert(make_pair(types[j], action));
                // 插入 Goto 表
                else {
                    Symbol symbol(N_TERMINAL, 0, no_terminal[j-8]);
                    gotoTable[i].insert(make_pair(symbol, action));
                }

            }
        }
    }
}

Action SyntaxAnalyser::stringToAction(const string actionString) {
    ACTION_TYPE actionType;
    char c = actionString[0];
    if (c == 'a')
        actionType = ACCEPT;
    else if (c == 's')
        actionType = SHIFT;
    else if (c == 'r')
        actionType = REDUCE;
    else
        actionType = GOTO;
    int num = 0;
    for (int i = 1; i < actionString.size(); ++i) {
        num = num*10 + actionString[i] - '0';
    }
    return Action(actionType, num);
}

SyntaxAnalyser::SyntaxAnalyser() {
    initMapTable();
}


double SyntaxAnalyser::analyse(const vector<Token> &tokenList) {
    stack<int> stateStack; // 状态栈
    stack<Symbol> symbolStack; // 符号栈
    int tokenIndex = 0; // 下一个Token

    stateStack.push(0); // 压入初始状态 0
    while (tokenIndex < tokenList.size()) {
        int state = stateStack.top();
        Token token = tokenList[tokenIndex];
        auto it = actionTable[state].find(token.type);
        if (it != actionTable[state].end()) {
            Action action = it->second;
            // 进行移进
            if (action.actionType == SHIFT) {
                symbolStack.push(Symbol(token));
                stateStack.push(action.num);
                tokenIndex++;
            // 进行归约
            } else if (action.actionType == REDUCE) {
                int popNum = grammarTable[action.num].size() - 3;
                double value[3] = {0};
                for (int i = 0; i < popNum; ++i) {
                    stateStack.pop();
                    value[i] = symbolStack.top().value;
                    symbolStack.pop();
                }
                // 归约时计算值
                double newValue = calculateValue(value, action.num);
                Symbol symbol(N_TERMINAL, newValue, grammarTable[action.num][0]);
                symbolStack.push(symbol);
                auto iter = gotoTable[stateStack.top()].find(symbol);
                // goto
                if (iter != gotoTable[stateStack.top()].end()) {
                    Action gotoAction = iter->second;
                    stateStack.push(gotoAction.num);
                }
            } else if (action.actionType == ACCEPT){
                // 识别成功，返回结果的值
                return symbolStack.top().value;
            }
        } else {
            // 出错，抛出语法错误异常
            throw CalculatorException("SyntaxError found");
        }
    }
    // 出错，抛出语法错误异常
    throw CalculatorException("SyntaxError found");
}

// numOfProduction 表示归约的产生式编号
double SyntaxAnalyser::calculateValue(const double *value, const int numOfProduction) {
    double newValue = 0;
    switch (numOfProduction) {
        case 1:
            newValue = value[2] + value[0]; // E->E+T
            break;
        case 2:
            newValue = value[2] - value[0]; // E->E-T
            break;
        case 4:
            newValue = value[2] * value[0]; // E->E*T
            break;
        case 5:
            // 除数不能为0
            if (value[0] == 0)
                throw CalculatorException("MathError: dividor can not be 0");
            newValue = value[2] / value[0]; // E->E/T
            break;
        case 3: // E->T
        case 6: // T->F
        case 8: // F->n
            newValue = value[0];
            break;
        case 7:
            newValue = value[1]; // F->(E)
            break;
        default:
            break;
    }
    return newValue;
}