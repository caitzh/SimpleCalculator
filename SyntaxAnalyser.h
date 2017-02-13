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

enum ACTION_TYPE {SHIFT, REDUCE, GOTO, ACCEPT};

struct Action {
    Action(ACTION_TYPE type, int n = 0) {
        actionType = type;
        num = n;
    }
    ACTION_TYPE actionType;
    int num;
};


class SyntaxAnalyser {
public:
    SyntaxAnalyser();
    bool analyse(const vector<Token> &tokenList);

private:
    void initMapTable();
    Action stringToAction(string actionString);
    double calculateValue(double value[], int numOfProduction);

    map<Symbol, Action> gotoTable[16];
    map<TOKEN_TYPE, Action> actionTable[16];
    static const string table[16][11];
    static const string grammarTable[9];
};


#endif //SIMPLECALCULATOR_SYNTAXANALYSER_H
