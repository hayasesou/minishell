#include "../../include/minishell.h"
#include "../../include/lexer.h"
#include "../../include/struct.h"

bool	consume_blank(char **line_ptr, char *line)
{
	if (is_blank(*line))
	{
		while (*line && is_blank(*line))
			line++;
		*line_ptr = line;
		return (true);
	}
	*line_ptr = line;
	return (false);
}

void	*word(char **line_ptr, char *line)
{
	const char	*start;
	char		*word;

	start = line;
	while (*line && !is_metacharacter(*line) && !is_quote(*line))
		line++;
	word = strndup(start, line - start);
	if (word == NULL)
		fatal_error("tokenize: word strndup error");
	*line_ptr = line;
	token_node_add(start, token_node_create(word, TK_WORD, GENERAL));
}
