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
    LexicalAnalyser(const string input = "");
    const vector<Token>& analyse(); // 进行词法分析，返回结果
    const vector<Token>& analyse(const string input); // 对参数进行词法分析，返回结果
    const vector<Token>& getResult(); // 获取词法分析结果

private:
    bool regonizeOperator(); // 识别运算符
    bool regonizeNumber(); // 识别数字
    bool regonizeWhiteSpace(); // 识别空白字符
    double stringToNum(const string s); // 将 string 转为数字(double)

    int index; // 指向下一个需要分析的字符
    string expression; // 需要分析的数学表达式
    vector<Token> result; // 词法分析结果, Token 序列
};


#endif //SIMPLECALCULATOR_LEXICALANALYSER_H
