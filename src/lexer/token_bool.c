#include "../../include/minishell.h"
#include "../../include/lexer.h"
#include "../../include/struct.h"

bool	is_blank(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

bool	is_word(char c)
{
	return (c && !is_operator(c) && !is_quote(c));
}

bool	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

bool	is_single_quote(char c)
{
	return (c == '\'');
}

bool	is_double_quote(char c)
{
	return (c == '\"');
}
