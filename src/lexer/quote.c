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

bool	is_single_quote_closed(char *line)
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

t_token	*single_quote_removal(char **line_ptr, char *line)
{
	char	*start;
	t_token	*token;

	start = line;
	if (is_single_quote(*line))
	{
		start++;
		line++;
	}
	while (*line && !(is_single_quote(*line)))
		line++;
	if (is_single_quote(*line))
	{
		line++;
		line_ptr = line;
		return (strndup(start, line - start));
	}
	else
		return (NULL);
}

t_token	*double_quote_expansion(char **line_ptr, char *line)
{
	//  パラメータ展開について処理を追加する
	char	*start;
	t_token	*token;

	start = line;
	if (is_double_quote(*line))
	{
		start++;
		line++;
	}
	while (*line && !(is_double_quote(*line)))
		line++;
	if (is_double_quote(*line))
	{
		line++;
		line_ptr = line;
		return (strndup(start, line - start));
	}
	else
		return (NULL);
}

