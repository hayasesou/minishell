#include "../../include/minishell.h"
#include "../../include/lexer.h"
#include "../../include/struct.h"

void	print_enum(t_token *node)
{
	if (node->type == TK_EMPTY)
		ft_printf(" %s\n", "EMPTY");
	else if (node->type == TK_PIPE)
		ft_printf(" %s\n", "PIPE");
	else if (node->type == TK_SINGLE_QUOTE)
		ft_printf(" %s\n", "SINGLE QUOTE");
	else if (node->type == TK_DOUBLE_QUOTE)
		ft_printf(" %s\n", "DOUBLE QUOTE");
	else if (node->type == TK_REDIR_IN)
		ft_printf(" %s\n", "REDIRECT IN");
	else if (node->type == TK_REDIR_HEREDOC)
		ft_printf(" %s\n", "HEREDOC");
	else if (node->type == TK_REDIR_OUT)
		ft_printf(" %s\n", "REDIRECT OUT");
	else if (node->type == TK_REDIR_APPEND)
		ft_printf(" %s\n", "APPEND");
	else
		print_enum_utils(node);
}

void	print_lexer(t_token *token_head)
{
	t_token	*tmp;

	tmp = token_head;
	while (tmp != token_head)
	{
		ft_printf("%s:", tmp->data);
		print_enum(tmp);
		tmp = tmp->next;
	}
}
