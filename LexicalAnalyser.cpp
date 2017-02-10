//
// Created by caitzh on 17-2-10.
//

#include "LexicalAnalyser.h"

LexicalAnalyser::LexicalAnalyser(string input) {
    expression = input;
    index = 0;
}

string LexicalAnalyser::analyse(string input) {
    expression = input;
    return analyse();
}

string LexicalAnalyser::analyse() {
    //TODO
    return "";
}

bool LexicalAnalyser::regonizeNumber() {
    //TODO
    return false;
}

bool LexicalAnalyser::regonizeOperator() {
    //TODO
    return false;
}
