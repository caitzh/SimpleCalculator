//
// Created by caitzh on 17-2-13.
//

#ifndef SIMPLECALCULATOR_CALCULATOR_H
#define SIMPLECALCULATOR_CALCULATOR_H

#include "LexicalAnalyser.h"
#include "SyntaxAnalyser.h"

class Calculator {
public:
    double calculate(string expression);
private:
    LexicalAnalyser lexicalAnalyser;
    SyntaxAnalyser syntaxAnalyser;
};


#endif //SIMPLECALCULATOR_CALCULATOR_H
