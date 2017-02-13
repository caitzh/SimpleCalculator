#include <iostream>
#include "Calculator.h"
#include "CalculatorException.h"

using namespace std;

int main() {
    string s;
    Calculator calculator;
    cout << "Please input a math expression[input q to quit]: " << endl;
    while (getline(cin, s)) {
        if (s[0] == 'q') break;
        try {
            cout << calculator.calculate(s) << endl;
            cout << "Please input a math expression[input q to quit]: " << endl;
        } catch (CalculatorException e) {
            cout << e.what() << endl;
            cout << "Please check and input again[input q to quit]: " << endl;
        } catch (exception e) {
            cout << e.what() << endl;
            cout << "Please check and input again[input q to quit]: " << endl;
        }
    }
    return 0;
}