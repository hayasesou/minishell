#include "minishell.h"

bool	is_env_name(char c)
{
	return (ft_isalnum(c) || c == '_');
}

bool	is_heredoc_expansion(t_token *token)
{
	return (token->prev && token->prev->type == TK_REDIR_HEREDOC);
}

bool	is_env_name_start(char c)
{
	return (ft_isalpha(c) || c == '_');
}

bool	is_env_name_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

bool	is_charset(char c, const char *charset)
{
	while (*charset)
	{
		if (c == *charset)
			return (true);
		charset++;
	}
	return (false);
}