#include "../include/minishell.h"
#include "../include/lexer.h"
#include "../include/struct.h"

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

t_token	*word(char **line_ptr, char *line)
{
	const char	*start;
	char		*word;

	start = line;
	if (*line && is_single_quote(*line))
	{
		word = quote_removal(&line, line);
		if (word == NULL)
			printf("Unclosed single quote");
		return (token_node_add(start, token_node_create(word, TK_WORD, SINGLE_QUOTE)));
	}
	else if (*line && is_double_quote(*line))
	{
		word = double_quote_expansion(&line, line);
		if (word == NULL)
			printf("Unclosed double quote");
		return (token_node_add(start, token_node_create(word, TK_WORD, DOUBLE_QUOTE)));
	}
	while (*line && !is_metacharacter(*line))
		line++; // 普通の文字の時
	word = strndup(start, line - start);
	if (word == NULL)
		fatal_error("tokenize: word strndup error");
	*line_ptr = line;
	return (token_node_add(start, token_node_create(word, TK_WORD, GENERAL)));
}
