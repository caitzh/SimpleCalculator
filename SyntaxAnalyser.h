//
// Created by caitzh on 17-2-11.
//

#ifndef SIMPLECALCULATOR_SYNTAXANALYSER_H
#define SIMPLECALCULATOR_SYNTAXANALYSER_H

#include "Symbol.h"
#include <map>
#include <stack>
#include <vector>
using namespace std;

// Action 类型, 移进、规约、GOTO(前进)、接受
enum ACTION_TYPE {SHIFT, REDUCE, GOTO, ACCEPT};

// Action 类
struct Action {
    Action(ACTION_TYPE type, int n = 0) {
        actionType = type;
        num = n;
    }
    ACTION_TYPE actionType;

    /*
     * actionType == SHIFT 或 GOTO 时, num 表示下一个状态
     * actionType == REDUCE 时, num 表示 规约的产生式编号
     * actionType == ACCEPT 时, num 无意义
     */
    int num;
};


class SyntaxAnalyser {
public:
    SyntaxAnalyser();
    double analyse(const vector<Token> &tokenList);

private:
    void initMapTable(); //初始化 ACTION表 和 GOTO表
    Action stringToAction(const string actionString); // string 转为 Action
    // 根据语法制导翻译规则求值
    double calculateValue(const double value[], const int numOfProduction);

    map<Symbol, Action> gotoTable[16]; // GOTO表
    map<TOKEN_TYPE, Action> actionTable[16]; // ACTION表
    static const string table[16][11]; // 用于初始化 ACTION表 和 GOTO表
    static const string grammarTable[9]; // 记录上下文无关文法, 即各个产生式
};


#endif //SIMPLECALCULATOR_SYNTAXANALYSER_H
