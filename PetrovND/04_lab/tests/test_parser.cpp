#include <gtest.h>
#include "parser.h"

TEST(parser, isValid_false_case1) {
	vector<string> infixExpression = { "+", "A", "+", "BC" };
	ASSERT_FALSE(Parser::isValidExpression(infixExpression));
}

TEST(parser, isValid_false_case2) {
	vector<string> infixExpression = { "A", "+", "BC", "+" };
	ASSERT_FALSE(Parser::isValidExpression(infixExpression));
}

TEST(parser, isValid_false_case3) {
	vector<string> infixExpression = { "A", "+", "BC", "+", "-", "5"};
	ASSERT_FALSE(Parser::isValidExpression(infixExpression));
}

TEST(parser, isValid_false_case4) {
	vector<string> infixExpression = { "(", "+", "BC", "+", "A", ")" };
	ASSERT_FALSE(Parser::isValidExpression(infixExpression));
}

TEST(parser, isValid_true) {
	vector<string> infixExpression = { "A", "+", "BC", "+", "5" };
	ASSERT_TRUE(Parser::isValidExpression(infixExpression));
}

TEST(parser, splitExpression_normal) {
    string expression1 = "3+5*(2-8)/2";
    vector<string> expectedTokens1 = { "3", "+", "5", "*", "(", "2", "-", "8", ")", "/", "2" };

    EXPECT_EQ(Parser::splitExpression(expression1), expectedTokens1);
}

TEST(parser, splitExpression_with_spaces) {
	string expression1 = "   1   +  2 * 3 ";
	vector<string> expectedTokens1 = { "1", "+", "2", "*", "3" };

	EXPECT_EQ(Parser::splitExpression(expression1), expectedTokens1);
}

TEST(parser, splitExpression_empty_expression) {
	string expression1 = "";
	vector<string> expectedTokens1 = {};

	EXPECT_EQ(Parser::splitExpression(expression1), expectedTokens1);
}

TEST(parser, infixToPostfix_normal) {
    vector<string> infixExpression1 = { "3", "+", "5", "*", "(", "2", "-", "8", ")", "/", "2" };
    vector<string> expectedPostfix1 = { "3", "5", "2", "8", "-", "*", "2", "/", "+" };

    EXPECT_EQ(Parser::infixToPostfix(infixExpression1), expectedPostfix1);
}

TEST(parser, infixToPostfix_empty_expression) {
	vector<string> infixExpression1 = {};
	vector<string> expectedPostfix1 = {};

	EXPECT_EQ(Parser::infixToPostfix(infixExpression1), expectedPostfix1);
}

TEST(parser, evaluate_case1) {
	vector<string> postfixExpression = { "2", "3", "+" };
	map<string, double> operandValues = { {"2", 2.0}, {"3", 3.0} };
	double result = Parser::evaluatePostfixExpression(operandValues, postfixExpression);
	EXPECT_DOUBLE_EQ(result, 5.0);
}

TEST(parser, evaluate_case2) {
	vector<string> postfixExpression = { "A", "B", "+", "C", "*" };
	map<string, double> operandValues = { {"A", 2.0}, {"B", 3.0}, {"C", 4.0} };
	double result = Parser::evaluatePostfixExpression(operandValues, postfixExpression);
	EXPECT_DOUBLE_EQ(result, 20.0);
}

TEST(parser, evaluate_case3) {
	vector<string> postfixExpression = { "AB", "5.5", "+", "C", "*" };
	map<string, double> operandValues = { {"AB", 2.0}, {"5.5", 5.5}, {"C", 4.0} };
	double result = Parser::evaluatePostfixExpression(operandValues, postfixExpression);
	EXPECT_DOUBLE_EQ(result, 30.0);
}

TEST(parser, evaluate_zero_div) {
	vector<string> postfixExpression = { "AB", "C", "/"};
	map<string, double> operandValues = { {"AB", 2.0}, {"C", 0.0} };
	ASSERT_ANY_THROW(Parser::evaluatePostfixExpression(operandValues, postfixExpression));
}