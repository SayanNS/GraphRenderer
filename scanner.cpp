//
// Created by sayan on 24.07.2022.
//

#include "scanner.h"
#include <istream>
#include <algorithm>

scanner::scanner(std::istream &is)
	: input(is)
{
}

token scanner::getNextToken()
{
	std::string text;

	while (input.peek() == ' ') {
		input.get();
	}

	if (input.peek() == '(') {
		text.push_back(static_cast<char>(input.get()));
		return token(token::category::open_parenthesize, std::move(text));
	}

	if (input.peek() == ')') {
		text.push_back(static_cast<char>(input.get()));
		return token(token::category::close_parenthesize, std::move(text));
	}

	if (input.peek() == 'x') {
		text.push_back(static_cast<char>(input.get()));
		return token(token::category::variable, std::move(text));
	}

	if (input.peek() == '+' || input.peek() == '-') {
		text.push_back(static_cast<char>(input.get()));
		return token(token::category::additive_operator, std::move(text));
	}

	if (input.peek() == '*' || input.peek() == '/') {
		text.push_back(static_cast<char>(input.get()));
		return token(token::category::multiplicative_operator, std::move(text));
	}

	while (!(input.peek() == ' ' || input.peek() == '(' || input.peek() == ')' || input.eof()
			|| input.peek() == '+' || input.peek() == '-' || input.peek() == '*' || input.peek() == '/')) {
		text.push_back(static_cast<char>(input.get()));
	}

	if (isNumber(text)) {
		return token(token::category::number, std::move(text));
	}

	if (text == "sin") {
		return token(token::category::sin, std::move(text));
	}

	if (text == "cos") {
		return token(token::category::cos, std::move(text));
	}

	throw ScannerException();
}

bool scanner::isNumber(std::string &text)
{
	return std::all_of(text.begin(), text.end(), [] (char c)
	{
		if (c < 48 || c > 57)
			return false;

		return true;
	});
}
