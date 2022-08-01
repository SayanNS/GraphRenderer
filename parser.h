//
// Created by sayan on 24.07.2022.
//

#ifndef PARSER_PARSER_H
#define PARSER_PARSER_H


#include "scanner.h"
#include "function.h"

struct ParserException : std::exception
{
};

class parser
{
public:
	explicit parser(std::istream &is);
	std::unique_ptr<Function> parse();

private:
	std::unique_ptr<Function> expression();
	std::unique_ptr<Function> primaryExpression();
	std::unique_ptr<Function> additiveExpression();
	std::unique_ptr<Function> multiplicativeExpression();
	std::unique_ptr<Function> parenthesizedExpression();

	std::unique_ptr<Function> number();
	std::unique_ptr<Function> variable();
	std::unique_ptr<Function> inverse();
	std::unique_ptr<Function> sinus();
	std::unique_ptr<Function> cosine();

	token eat(token::category category);

	scanner input;
	token current_token;
};


#endif //PARSER_PARSER_H
