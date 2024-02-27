#include "parser.h"
#include <iostream>
int main() {
    string inputExpression;
    cout << "Enter expression: ";
    getline(cin, inputExpression);

    vector<string> tokens = Parser::splitExpression(inputExpression);

    if (!(Parser::isValidExpression(tokens))) {
        cerr << "ERROR: Invalid Expression!";
        return 1;
    }

    vector<string> res = Parser::infixToPostfix(tokens);
    for (int i = 0; i < res.size(); i++) cout << res[i] << ", ";
    cout << endl;

    map<string, double> opVal = Parser::getOperandValues(tokens);
    try{
        cout << Parser::evaluatePostfixExpression(opVal, res);
    }
    catch (const char* error){
        cout << error;
    }
    return 0;
}