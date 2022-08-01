//
// Created by sayan on 24.07.2022.
//

#include "token.h"

token::token(category category, std::string &&text)
	: the_kind(category)
	, the_text(std::move(text))
{
}

std::string token::text() const
{
	return the_text;
}

token::category token::kind() const
{
	return the_kind;
}
