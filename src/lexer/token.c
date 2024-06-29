#include "../../include/lexer.h"

bool	is_blank(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

bool	consume_blank(char **line_ptr, char *line)
{
	if (is_blank(*line))
	{
		while (*line && is_blank(*line))
			line++;
		*line_ptr = line;
		return (true);
	}
	*line_ptr = line; // これ必要？
	return (false);
}

bool	start_with_operator(const char *s, const char *operator)
{
	return (memcmp(s, operator, srlen(operator)) == 0);
}

bool	is_operator(const char *s)
{
	static char *const	operators[] = {"|", "||", "&", "&&", ";", ";;", "(", ")", "\n"};
	size_t				i;

	i = 0;
	while (i < sizeof(operators) / sizeof(*operators))
	{
		if (start_with_operator(s, operators[i]))
			return (true);
		i++;
	}
	return (false);
}

t_token	*operator(char **line_ptr, char *line)
{
	static char *const	operators[] = {"|", "||", "&", "&&", ";", ";;", "(", ")", "\n"};
	size_t				i;
	char				*op;

	i = 0;
	while (i < sizeof(operators) / sizeof(*operators))
	{
		if (start_with_operator(line, operators[i]))
		{
			op = strdup(operators[i]);
			if (op == NULL)
				fatal_error("tokenize: operator, strdup error");
			*line_ptr = line + strlen(op);
			return (new_token(op, TK_OP));
		}
		i++;
	}
	assert_error("tokenize: operator, unexpected operator");
}

bool	is_metacharacter(char c)
{
	return (c && strchr("|&;()<> \t\n", c));
}

bool	is_word(const char *s)
{
	return (*s && !is_metacharacter(*s));
}

t_token	*word(char **line_ptr, char *line)
{
	const char	*start;
	char		*word;

	start = line;
	while (*line && !is_metacharacter(*line))
		line++;
	word = strndup(start, line - start);
	if (word == NULL)
		fatal_error("tokenize: word strndup error");
	*line_ptr = line;
	return (add_token(word, TK_WORD));
}


