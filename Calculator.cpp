//
// Created by caitzh on 17-2-13.
//

#include "Calculator.h"

double Calculator::calculate(string expression) {
    const vector<Token> tokenList = lexicalAnalyser.analyse(expression);
    return syntaxAnalyser.analyse(tokenList);
}
