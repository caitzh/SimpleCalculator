//
// Created by caitzh on 17-2-13.
//

#ifndef SIMPLECALCULATOR_CALCULATOREXCEPTION_H
#define SIMPLECALCULATOR_CALCULATOREXCEPTION_H

#include <string>
#include <exception>
using std::string;
using std::exception;

class CalculatorException : public exception {
public:
    CalculatorException(string message);
    string what();
private:
    string message;
};


#endif //SIMPLECALCULATOR_CALCULATOREXCEPTION_H
