#include "../../include/minishell.h"
#include "../../include/lexer.h"
#include "../../include/struct.h"

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
