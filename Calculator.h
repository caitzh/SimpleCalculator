//
// Created by caitzh on 17-2-13.
//

#ifndef SIMPLECALCULATOR_CALCULATOR_H
#define SIMPLECALCULATOR_CALCULATOR_H

#include "LexicalAnalyser.h"
#include "SyntaxAnalyser.h"

class Calculator {
public:
    double calculate(string expression); // 计算表达式的值
private:
    LexicalAnalyser lexicalAnalyser; // 词法分析器
    SyntaxAnalyser syntaxAnalyser; // 语法分析器
};


#endif //SIMPLECALCULATOR_CALCULATOR_H
