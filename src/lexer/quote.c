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

void quote(char **line_ptr, char *line, t_token *token, bool space_before)
{
    char quote_char = *line;
    char *start = line + 1;  // クォートの次の文字から始める
    line++;

    while (*line && *line != quote_char)
        line++;

    if (*line == quote_char)
    {
        int length = line - start;  // クォートを含まない長さ
        char *quoted_str = strndup(start, length);
        if (quoted_str == NULL)
            fatal_error("quote: strndup error");

        t_token_type type;
        if (quote_char == '\'')
            type = space_before ? TK_SPACE_SINGLE_QUOTE : TK_SINGLE_QUOTE;
        else
            type = space_before ? TK_SPACE_DOUBLE_QUOTE : TK_DOUBLE_QUOTE;

        token_node_add(token, token_node_create(quoted_str, type));
        free(quoted_str);
        *line_ptr = line + 1;  // 終わりのクォートの次の文字へ
    }
    else
    {
        err_exit(start - 1, "Unclosed quote", 1);
    }
}