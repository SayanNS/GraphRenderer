//
// Created by sayan on 24.07.2022.
//

#include "parser.h"

parser::parser(std::istream &is)
		: input(is)
		, current_token(input.getNextToken())
{
}

std::unique_ptr<Function> parser::parse()
{
	return expression();
}

std::unique_ptr<Function> parser::expression()
{
	return additiveExpression();
}

std::unique_ptr<Function> parser::additiveExpression()
{
	std::unique_ptr<Function> left = multiplicativeExpression();

	while (current_token.kind() == token::category::additive_operator) {
		if (eat(token::category::additive_operator).text() == "+") {
			left = std::make_unique<SumFunction>(std::move(left), multiplicativeExpression());
		} else {
			left = std::make_unique<MinusFunction>(std::move(left), multiplicativeExpression());
		}
	}

	return left;
}

std::unique_ptr<Function> parser::multiplicativeExpression()
{
	std::unique_ptr<Function> left = primaryExpression();

	while (current_token.kind() == token::category::multiplicative_operator) {
		if (eat(token::category::multiplicative_operator).text() == "*") {
			left = std::make_unique<MultiplyFunction>(std::move(left), primaryExpression());
		} else {
			left = std::make_unique<DivideFunction>(std::move(left), primaryExpression());
		}
	}

	return left;
}

std::unique_ptr<Function> parser::primaryExpression()
{
	switch (current_token.kind()) {
	case token::category::open_parenthesize:
		return parenthesizedExpression();
	case token::category::variable:
		return variable();
	case token::category::number:
		return number();
	case token::category::sin:
		return sinus();
	case token::category::cos:
		return cosine();
	case token::category::additive_operator:
		return inverse();
	default:
		throw ParserException();
	}
}

std::unique_ptr<Function> parser::parenthesizedExpression()
{
	eat(token::category::open_parenthesize);
	std::unique_ptr<Function> function = expression();
	eat(token::category::close_parenthesize);
	return function;
}

std::unique_ptr<Function> parser::number()
{
	return std::make_unique<ConstFunction>(std::stoi(eat(token::category::number).text()));
}

std::unique_ptr<Function> parser::variable()
{
	eat(token::category::variable);
	return std::make_unique<LinearFunction>();
}

token parser::eat(token::category category)
{
	token current = current_token;

	if (current.kind() != category) {
		throw ParserException();
	}

	current_token = input.getNextToken();
	return current;
}

std::unique_ptr<Function> parser::sinus()
{
	eat(token::category::sin);
	return std::make_unique<SinFunction>(parenthesizedExpression());
}

std::unique_ptr<Function> parser::cosine()
{
	eat(token::category::cos);
	return std::make_unique<CosFunction>(parenthesizedExpression());
}

std::unique_ptr<Function> parser::inverse()
{
	if (eat(token::category::additive_operator).text() == "-") {
		return std::make_unique<InverseFunction>(primaryExpression());
	} else {
		return primaryExpression();
	}
}

