#pragma once
#ifndef _PARSER_H
#define _PARSER_H

#include "stack.h"
#include <map>
#include <vector>
#include <string>
using namespace std;

class Parser {
private:
	static bool isOperator(const string& token);
	static int getPrecedence(const string& op);
public:
	static bool isValidExpression(const vector<string>& infixExpression);
	static vector<string> splitExpression(const string& expression);
	static vector<string> infixToPostfix(const vector<string>& infixExpression);
	static map<string, double> getOperandValues(const vector<string>& tokens);
	static double evaluatePostfixExpression(const map<string, double>& operandValues,
		vector<string>& postfixExpression);
};

#endif // !_PARSER_H
