//
// Created by caitzh on 17-2-13.
//

#include "CalculatorException.h"

CalculatorException::CalculatorException(string message)
        : exception(), message(message) {}

string CalculatorException::what() {
    return message;
}