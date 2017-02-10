//
// Created by caitzh on 17-2-10.
// 词法分析器

#ifndef SIMPLECALCULATOR_LEXICALANALYSER_H
#define SIMPLECALCULATOR_LEXICALANALYSER_H

#include <vector>
#include <string>
#include "Token.h"
using namespace std;

class LexicalAnalyser {
public:
    LexicalAnalyser(string input);
    string analyse();
    string analyse(string input);
    bool regonizeOperator();
    bool regonizeNumber();

private:
    int index; // 指向下一个需要分析的字符
    string expression; // 需要分析的数学表达式
    vector<Token> result; // 词法分析结果, Token 序列
};


#endif //SIMPLECALCULATOR_LEXICALANALYSER_H
