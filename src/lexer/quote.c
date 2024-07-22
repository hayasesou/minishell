#include "minishell.h"

bool	is_single_quote_closed(char *line)
{
	while (*line)
	{
		line++;
		if (*line == '\'')
			return (true);
	}
	printf("single quote is not closed\n");
	return (false);
}

bool	is_double_quote_closed(char *line)
{
	while (*line)
	{
		line++;
		if (*line == '\"')
			return (true);
	}
	printf("double quote is not closed\n");
	return (false);
}

char	*single_quote_removal(char *str)
{
	char	*start;

	str++;
	start = str;
	while (*str && !(is_single_quote(*str)))
		str++;
	if (is_single_quote(*str))
		return (strndup(start, str - start));
	else
		return (NULL);
}

char	*double_quote_removal(char *str)
{
	char	*start;

	str++;
	start = str;
	while (*str && !(is_double_quote(*str)))
		str++;
	if (is_double_quote(*str))
		return (strndup(start, str - start));
	else
		return (NULL);
}

void	quote(char **line_ptr, char *line, t_token *token)
{
	char			*word;
	t_token_state	type;

	if (*line && is_single_quote(*line))
	{
        if (is_single_quote_closed(line))
    		word = single_quote_removal(line);
		else
			err_exit(line, "Unclosed single quote", 1); // locationとstatusの確認
		type = SINGLE_QUOTE;
	}
	else if (*line && is_double_quote(*line))
	{
		if (is_double_quote_closed(line))
			word = double_quote_removal(line);
		else
			err_exit(line, "Unclosed single quote", 1); // locationとstatusの確認
		type = DOUBLE_QUOTE;
	}
	else
		err_exit(line, "not quote", 0); // errorの種類あとで変える
	if (word == NULL)
		fatal_error("tokenize: word strndup error");
	token_node_add(token, token_node_create(word, TK_WORD, type));
    *line_ptr += strlen(word) + 2; // +2はクオーテーション2個分
}
