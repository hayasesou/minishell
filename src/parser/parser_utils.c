#include "minishell.h"

t_redirect_type get_redirect_type(t_token_type type)
{
    if (type == TK_REDIR_IN)
        return IN_FILE;
    else if (type == TK_REDIR_OUT)
        return OUT_FILE;
    else if (type == TK_REDIR_APPEND)
        return APPEND;
    else if (type == TK_REDIR_HEREDOC)
        return HEREDOC;
    else
        return UNKNOWN;
}