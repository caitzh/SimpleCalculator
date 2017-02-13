//
// Created by caitzh on 17-2-13.
//

#ifndef SIMPLECALCULATOR_CALCULATOREXCEPTION_H
#define SIMPLECALCULATOR_CALCULATOREXCEPTION_H

#include <string>
#include <exception>
using std::string;
using std::exception;

// 自定义异常类，表示计算表达式时发生的各种异常
class CalculatorException : public exception {
public:
    CalculatorException(string message);
    const string what();
private:
    string message; // 异常信息
};


#endif //SIMPLECALCULATOR_CALCULATOREXCEPTION_H
