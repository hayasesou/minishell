#include "../../include/minishell.h"
#include "../../include/lexer.h"
#include "../../include/struct.h"

bool	is_operator(const char *s)
{
	static char *const	operators[] = {"|", ">", "<", "\n"};
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
	static char *const	operators[] = {"|", "&", "(", ")", "\n"};
	size_t				i;
	char				*op;
	char				*start;

	i = 0;
	start = line;
	while (i < sizeof(operators) / sizeof(*operators))
	{
		if (start_with_operator(line, operators[i]))
		{
			op = strdup(operators[i]);
			if (op == NULL)
				fatal_error("tokenize: operator, strdup error");
			*line_ptr = line + strlen(op);
			return (token_node_add(start, token_node_create(op, TK_OP, GENERAL)));
		}
		i++;
	}
	//assert_error("tokenize: operator, unexpected operator");
	return (NULL); // errorにしておわらせる, 一時的にreturnを書かないと動かないからnull返している
}

bool	start_with_operator(const char *s, const char *operator)
{
	return (memcmp(s, operator, strlen(operator)) == 0);
}
