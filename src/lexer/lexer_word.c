#include "minishell.h"

void word(char **line_ptr, char *line, t_token *token, bool space_before)
{
    char *start;
    char *word;

    start = line;
    while (*line && is_word(*line))
        line++;
    word = ft_strndup(start, line - start);
    if (word == NULL)
        fatal_error("tokenize: word strndup error");
    *line_ptr = line;
    token_node_add(token, token_node_create(word, space_before ? TK_SPACE_WORD : TK_WORD));
}
