#include "minishell.h"

bool    is_string(t_token *token)
{
    if (token->type == TK_WORD || token->type == TK_SINGLE_QUOTE || token->type == TK_DOUBLE_QUOTE)
        return (true);
    return (false);
}

bool    is_in_quote(t_token *token)
{
    if (token->type == TK_SINGLE_QUOTE || token->type == TK_DOUBLE_QUOTE)
        return (true);
    return (false);
}

bool    is_redirect(t_token *token)
{
    if (token->type == TK_REDIR_IN || token->type == TK_REDIR_OUT || token->type == TK_REDIR_APPEND || token->type == TK_REDIR_HEREDOC)
        return (true);
    return (false);
}

bool    is_pipe(t_token *token)
{
    if (token->type == TK_PIPE)
        return (true);
    return (false);
}   

bool    is_cat_token(t_token *token)
{
    if (is_in_quote(token) && is_string(token->next))
        return (true);
    else if (is_string(token) && is_in_quote(token->next))
        return (true);
    else if (is_in_quote(token) && is_in_quote(token->next))
        return (true);
    else
        return (false);

}
