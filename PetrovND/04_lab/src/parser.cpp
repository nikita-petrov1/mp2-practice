#include <iostream>
#include <algorithm>
#include "parser.h"

vector<string> Parser::splitExpression(const string& expression) {
    vector<string> result;
    string currentToken;

    for (char ch : expression) {
        if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')') {
            if (!currentToken.empty()) {
                result.push_back(currentToken);
                currentToken.clear();
            }
            result.push_back(string(1, ch));
        }
        else if (isspace(ch)) {
            continue;
        }
        else {
            currentToken += ch;
        }
    }
    if (!currentToken.empty()) {
        result.push_back(currentToken);
    }
    return result;
}

int Parser::getPrecedence(const string& op) {
    if (op == "+" || op == "-") {
        return 1;
    }
    else if (op == "*" || op == "/") {
        return 2;
    }
    return 0;
}
bool Parser::isOperator(const string& token) {
    return (token == "+" || token == "-" || token == "*" || token == "/");
}

bool Parser::isValidExpression(const vector<string>& infixExpression) {
    if (isOperator(infixExpression[0])) return 0;
    else if (isOperator(infixExpression[infixExpression.size() - 1])) return 0;
    else{
        for (int i = 0; i < infixExpression.size() - 1; i++) {
            if(isOperator(infixExpression[i]) && isOperator(infixExpression[i+1])) return 0;
            if(infixExpression[i] == "(" && isOperator(infixExpression[i + 1])) return 0;
        }
    }
    return 1;
}


map<string, double> Parser::getOperandValues(const vector<string>& tokens) {
    map<string, double> operandValues;

    for (const auto& token : tokens) {
        if (token != "+" && token != "-" && token != "*" && token != "/" && token != "(" && token != ")") {
            if (operandValues.find(token) == operandValues.end()) {
                double value;
                if (token.find_first_not_of("0123456789.") == string::npos) {
                    operandValues[token] = stod(token);
                    continue;
                }
                cout << "Enter operand value " << token << ": ";
                cin >> value;
                operandValues[token] = value;
            }
        }
    }
    return operandValues;
}

vector<string> Parser::infixToPostfix(const vector<string>& infixExpression) {
    Stack<string>operands;
    Stack<string> operators;

    for (const string& token : infixExpression) {
        if (isalnum(token[0])) {
            operands.push(token);
        }
        else if (isOperator(token)) {
            while (!operators.isEmpty() && getPrecedence(operators.top()) >= getPrecedence(token)) {
                operands.push(operators.top());
                operators.pop();
            }
            operators.push(token);
        }
        else if (token == "(") {
            operators.push(token);
        }
        else if (token == ")") {
            while (!operators.isEmpty() && operators.top() != "(") {
                operands.push(operators.top());
                operators.pop();
            }
            operators.pop();
        }
    }

    while (!operators.isEmpty()) {
        operands.push(operators.top());
        operators.pop();
    }

    vector<string> postfix;

    while (!operands.isEmpty()){
        postfix.push_back(operands.top());
        operands.pop();
    }
    reverse(postfix.begin(), postfix.end());
    return postfix;
}

double Parser::evaluatePostfixExpression(const map<string, double>& operandValues, vector<string>& postfixExpression) {
    Stack<double> resultStack;

    for (int i = 0; i < postfixExpression.size(); i++) {
        const string token = postfixExpression[i];

        if (!(isOperator(token))) {
            if (operandValues.find(token) != operandValues.end()) {
                resultStack.push(operandValues.at(token));
            }
            else {
                throw invalid_argument("Error: operands value not exist.\n");
                return 0.0;
            }
        }
        else {
            double operand2 = resultStack.top();
            resultStack.pop();

            double operand1 = resultStack.top();
            resultStack.pop();

            if (token == "+") {
                resultStack.push(operand1 + operand2);
            }
            else if (token == "-") {
                resultStack.push(operand1 - operand2);
            }
            else if (token == "*") {
                resultStack.push(operand1 * operand2);
            }
            else if (token == "/") {
                if (operand2 == 0) {
                    throw "ERROR: divizion by zero.\n";
                    return 0.0;
                }
                resultStack.push(operand1 / operand2);
            }
        }
    }
    return resultStack.top();
}