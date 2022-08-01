//
// Created by sayan on 24.07.2022.
//

#ifndef PARSER_SCANNER_H
#define PARSER_SCANNER_H


#include "token.h"

struct ScannerException : std::exception
{
};

class scanner
{
public:
	explicit scanner(std::istream &is);

	token getNextToken();

private:
	static bool isVariable(char symbol);
	static bool isNumber(std::string &text);
	static bool isAdditiveOperator(char symbol);
	static bool isMultiplicativeOperator(char symbol);

	std::istream &input;
};


#endif //PARSER_SCANNER_H
