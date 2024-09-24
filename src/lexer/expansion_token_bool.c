#include "minishell.h"

bool is_double_quote_expansion(t_token_type type)
{
    return (type == TK_DOUBLE_QUOTE || type == TK_SPACE_DOUBLE_QUOTE);
}

bool is_word_expansion(t_token_type type)
{
    return (type == TK_WORD || type == TK_SPACE_WORD);
}
