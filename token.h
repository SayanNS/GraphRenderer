//
// Created by sayan on 24.07.2022.
//

#ifndef PARSER_TOKEN_H
#define PARSER_TOKEN_H


#include <string>

class token
{
public:
	enum class category
	{
		sin,
		cos,
		number,
		variable,
		additive_operator,
		multiplicative_operator,
		open_parenthesize,
		close_parenthesize,
	};

	token(token const &) = default;
	token &operator=(token const &) = default;

	std::string text() const;
	category kind() const;

private:
	friend class scanner;

	token() = default;
	token(category category, std::string &&text);

	std::string the_text;
	category the_kind;
};


#endif //PARSER_TOKEN_H
