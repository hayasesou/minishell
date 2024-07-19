#include "../../include/minishell.h"
#include "../../include/lexer.h"
#include "../../include/struct.h"

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

t_token	*single_quote_removal(char *str)
{
	char	*start;
	t_token	*token;

	str++;
	start = str;
	while (*str && !(is_single_quote(*str)))
		str++;
	if (is_single_quote(*str))
		return (strndup(start, str - start));
	else
		return (NULL);
}

t_token	*double_quote_removal(char *str)
{
	char	*start;
	t_token	*token;

	str++;
	start = str;
	while (*str && !(is_double_quote(*str)))
		str++;
	if (is_double_quote(*str))
		return (strndup(start, str - start));
	else
		return (NULL);
}

void	quote(char **line_ptr, char *line)
{
	char			*word;
	t_token_type	type;

	if (*line && is_single_quote(*line))
	{
        if (is_single_puote_closed(line))
    		word = quote_removal(line);
		else
			err_exit(line, "Unclosed single quote", 1); // locationとstatusの確認
		type = SINGLE_QUOTE;
	}
	else if (*line && is_double_quote(*line))
	{
		if (is_double_puote_closed(*line))
			word = double_quote_expansion(line);
		else
			err_exit(line, "Unclosed single quote", 1); // locationとstatusの確認
		type = DOUBLE_QUOTE;
	}
	if (word == NULL)
		fatal_error("tokenize: word strndup error");
	token_node_add(line + 1, token_node_create(word, TK_WORD, type));
    *line_ptr += strlen(word) + 2; // +2はクオーテーション2個分
}
