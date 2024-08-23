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

void quote(char **line_ptr, char *line, t_token *token)
{
    char *word;
    t_token_type type;
    char quote_char = *line;

    if (quote_char == '\'')
    {
        if (!is_single_quote_closed(line))
            err_exit(line, "Unclosed single quote", 1);
        word = single_quote_removal(line);
        type = TK_SINGLE_QUOTE;  // Single quotes don't allow expansions, so it's just a word
    }
    else if (quote_char == '\"')
    {
        if (!is_double_quote_closed(line))
            err_exit(line, "Unclosed double quote", 1);
        word = double_quote_removal(line);
        type = TK_DOUBLE_QUOTE;  // We'll handle expansions later, for now it's a word
    }
    else
        err_exit(line, "not quote", 0);

    if (word == NULL)
        fatal_error("tokenize: word strndup error");
    token_node_add(token, token_node_create(word, type));
    *line_ptr += strlen(word) + 2;  // +2 for the quotes
    free(word);
}